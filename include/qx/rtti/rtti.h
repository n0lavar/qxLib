/**

    @file      rtti.h
    @brief     RTTI system based on polymorphism
    @details   Using qx::rtti_root and QX_RTTI_CLASS
               will let you to use RTTI advantages without enabling
               RTTI in compiler's flags
               common logic is taken from
               https://github.com/qualab/xakep-RTTI (Vladimir Kerimov, qualab)
    @author    Khrapov
    @date      24.08.2020
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/string/string_hash.h>
#include <qx/macros/common.h>
#include <qx/macros/copyable_movable.h>
#include <qx/meta/tuple_utils.h>
#include <qx/rtti/class_id.h>
#include <qx/rtti/rtti_naming_strategy.h>

#include <array>
#include <span>

namespace qx
{

// utility class to let you use std::derived_from
class rtti_pure_base
{
    QX_COPYMOVABLE(rtti_pure_base);

    template<class naming_strategy_t>
    friend class rtti_root;

public:
    auto operator<=>(const rtti_pure_base&) const = default;

private:
    rtti_pure_base() = default;
};

/**

    @class   rtti_root
    @brief   Polymorphic base for qx class identity and inheritance queries.
    @details Derive an RTTI hierarchy from this type and use QX_RTTI_CLASS in each
             derived class to supply its identity and extend the inheritance chain.
             This system does not require compiler RTTI.

             Static queries describe the type declaring them; virtual queries
             describe the object's most-derived registered type. is<T>() checks
             exact identity, while is_derived_from<T>() also accepts base types.

             The naming strategy affects class names, not class identifiers.
             Names may be empty or shared by several types. The protected destructor
             prevents deleting an object directly through an rtti_root pointer.
    @tparam  naming_strategy_t - strategy providing get_name(string_view) to transform
                                 the compiler-generated type signature into a class name
    @see     rtti_naming_strategy.h
    @author  Khrapov
    @date    10.09.2021

**/
template<class naming_strategy_t = rtti_naming_strategy_class_name>
class QX_EMPTY_BASES rtti_root : public rtti_pure_base
{
    QX_COPYMOVABLE(rtti_root);

public:
    using base_class_type        = rtti_root;
    using super_class_type       = rtti_root;
    using this_class_type        = rtti_root;
    using inheritance_tuple_type = std::tuple<this_class_type>;
    using naming_strategy_type   = naming_strategy_t;

public:
    rtti_root() noexcept = default;

    auto operator<=>(const rtti_root&) const = default;

    /**
        @brief  Test exact identity or membership in the object's RTTI base chain.
        @tparam T - candidate type exposing QX_RTTI_CLASS()
        @return   - true for the object's registered type and its registered bases
    **/
    template<class T>
    bool is_derived_from() const noexcept;

    /**
        @brief  Compare the object's dynamic class identifier with T's identifier.
        @tparam T - candidate type exposing QX_RTTI_CLASS()
        @return   - true only when the identifiers match; base types are not accepted
    **/
    template<class T>
    bool is() const noexcept;

    /**
        @brief   Compare against the class name selected by the naming strategy.
        @note    Name equality does not imply type identity when the naming strategy
                 produces duplicate names, such as rtti_naming_strategy_empty.
        @param   svClassName - expected result of get_class_name(), not a base-class name
        @return              - true when the names match exactly
    **/
    bool is(string_view svClassName) const noexcept;

    /**
        @brief  Compare against the object's dynamic class identifier.
        @param  id - candidate for exact identity, not an inheritance query
        @return    - true when id equals get_class_id()
    **/
    bool is(const class_id& id) const noexcept;

    /**
        @brief  Test an identifier against the object's dynamic RTTI hierarchy.
        @param  id - candidate class identifier, including the object's own identifier
        @return    - true when id belongs to the registered type or one of its bases
    **/
    virtual bool is_derived_from_id(const class_id& id) const noexcept;

    /**
        @brief   Test an identifier against the declaring type's static RTTI hierarchy.
        @details rtti_root matches only its own identifier; QX_RTTI_CLASS extends
                 this comparison recursively through the declared base class.
        @param   id - candidate class identifier to find in the static base chain
        @return     - true when id belongs to the declaring type or one of its bases
    **/
    static constexpr bool is_derived_from_id_static(const class_id& id) noexcept;

    /**
        @brief  Apply the naming strategy to the declaring RTTI type's signature.
        @return - a class-name view that may be empty, depending on the strategy
    **/
    static constexpr string_view get_class_name_static() noexcept;

    /**
        @brief  Get the name of the object's most-derived registered RTTI type.
        @return - the naming strategy's result for the dynamic type; it may be empty
    **/
    virtual string_view get_class_name() const noexcept;

    /**
        @brief   Create the declaring RTTI type's identifier from its type signature.
        @note    The signature is compiler-dependent; identifiers are not a portable
                 format for persisting type identity across different builds.
        @return  - identifier independent of the selected class-name representation
    **/
    static constexpr class_id get_class_id_static() noexcept;

    /**
        @brief  Get the identifier of the object's most-derived registered RTTI type.
        @return - identifier used by exact-type comparisons and RTTI casts
    **/
    virtual class_id get_class_id() const noexcept;

    /**
        @brief   Get the registered inheritance chain in base-to-derived order.
        @return  - identifiers from the rtti_root specialization through the dynamic type
        @details QX_RTTI_CLASS returns a span backed by class-specific static storage,
                 rather than storage owned by the object.
    **/
    virtual std::span<const class_id> get_inheritance_sequence() const = 0;

protected:
    virtual ~rtti_root() noexcept = default;

    /**
        @brief   Traverse identifiers treated as bases by derived RTTI classes.
        @param   idBase - candidate identifier from an inheritance query
        @return        - true when an identifier matches during base-chain traversal
        @details The root compares against its own identifier. Macro-generated
                 overrides check their immediate base and continue recursively.
    **/
    virtual bool _is_base_id(const class_id& idBase) const noexcept;
};

namespace filters
{

template<class T>
constexpr auto is_derived_from = [](const auto& value)
{
    return value.template is_derived_from<T>();
};

template<class T>
constexpr auto is = [](const auto& value)
{
    return value.template is<T>();
};

} // namespace filters

/**
    @def   QX_RTTI_CLASS
    @brief Add dynamic identity and inheritance queries to a class in a qx RTTI hierarchy.
    @param thisClass - type being registered, used to generate its identifier and name
    @param ...       - immediate base type, either rtti_root or a type using QX_RTTI_CLASS
**/
#define QX_RTTI_CLASS(thisClass, ...)                                                                               \
                                                                                                                    \
public:                                                                                                             \
    using this_class_type  = thisClass;                                                                             \
    using super_class_type = __VA_ARGS__;                                                                           \
    using base_class_type  = typename super_class_type::base_class_type;                                            \
    using inheritance_tuple_type =                                                                                  \
        qx::tuple_utils::join_t<typename super_class_type::inheritance_tuple_type, this_class_type>;                \
                                                                                                                    \
public:                                                                                                             \
    static constexpr bool is_derived_from_id_static(const qx::class_id& id) noexcept                                \
    {                                                                                                               \
        return id == get_class_id_static() || super_class_type::is_derived_from_id_static(id);                      \
    }                                                                                                               \
    virtual bool is_derived_from_id(const qx::class_id& id) const noexcept override                                 \
    {                                                                                                               \
        static_assert(std::is_same_v<std::remove_cvref_t<decltype(*this)>, this_class_type>);                       \
        return is_derived_from_id_static(id);                                                                       \
    }                                                                                                               \
    static constexpr qx::string_view get_class_name_static() noexcept                                               \
    {                                                                                                               \
        return base_class_type::naming_strategy_type::get_name(qx::type_strings<this_class_type>::get_signature()); \
    }                                                                                                               \
    virtual qx::class_id get_class_id() const noexcept override                                                     \
    {                                                                                                               \
        return get_class_id_static();                                                                               \
    }                                                                                                               \
    static constexpr qx::class_id get_class_id_static() noexcept                                                    \
    {                                                                                                               \
        constexpr qx::class_id id = qx::class_id::create<this_class_type>();                                        \
        return id;                                                                                                  \
    }                                                                                                               \
    virtual qx::string_view get_class_name() const noexcept override                                                \
    {                                                                                                               \
        return get_class_name_static();                                                                             \
    }                                                                                                               \
    virtual std::span<const qx::class_id> get_inheritance_sequence() const override                                 \
    {                                                                                                               \
        static constexpr auto s_Ids = []()                                                                          \
        {                                                                                                           \
            std::array<qx::class_id, std::tuple_size_v<inheritance_tuple_type>> ids_;                               \
            qx::tuple_utils::iterate<inheritance_tuple_type>(                                                       \
                [&ids_]<class T, size_t I>()                                                                        \
                {                                                                                                   \
                    ids_[I] = T::get_class_id_static();                                                             \
                });                                                                                                 \
            return ids_;                                                                                            \
        }();                                                                                                        \
        return s_Ids;                                                                                               \
    }                                                                                                               \
                                                                                                                    \
protected:                                                                                                          \
    virtual bool _is_base_id(const qx::class_id& base_id) const noexcept override                                   \
    {                                                                                                               \
        return base_id == super_class_type::get_class_id_static() || super_class_type::_is_base_id(base_id);        \
    }                                                                                                               \
                                                                                                                    \
private:                                                                                                            \
    QX_EMPTY_MACRO

} // namespace qx

#include <qx/rtti/rtti.inl>
