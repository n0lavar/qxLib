/**

    @file      rtti_cast.h
    @author    Khrapov
    @date      9.09.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/rtti/rtti.h>
#include <qx/smart_ptr/link.h>

#include <memory>

namespace qx
{

/**
    @brief   Returns to_t* if from_t is inherited from Y, otherwise nullptr
    @tparam  to_t    - type to cast to
    @tparam  from_t  - type to cast from
    @param   pointer - a pointer to test
    @retval          - to_t* if from_t is inherited from pointer class, otherwise nullptr
**/
template<class to_t, class from_t>
    requires std::derived_from<from_t, rtti_pure_base> && std::derived_from<to_t, rtti_pure_base>
to_t* rtti_cast(from_t* pointer)
{
    if (pointer && pointer->template is_derived_from<to_t>())
        return static_cast<to_t*>(pointer);

    return nullptr;
}

/**
    @brief  Returns to_t* if from_t is inherited from Y, otherwise nullptr
    @tparam to_t   - type to cast to
    @tparam from_t - type to cast from
    @param  pValue - a pointer to test
    @retval        - to_t* if from_t is inherited from Y, otherwise nullptr
**/
template<class to_t, class from_t>
    requires std::derived_from<from_t, rtti_pure_base> && std::derived_from<to_t, rtti_pure_base>
to_t* rtti_cast(const std::shared_ptr<from_t>& pValue)
{
    if (pValue && pValue->template is_derived_from<to_t>())
        return static_cast<to_t*>(pValue.get());

    return nullptr;
}

/**
    @brief  Returns to_t* if from_t is inherited from Y, otherwise nullptr
    @tparam to_t   - type to cast to
    @tparam from_t - type to cast from
    @param  pValue - a pointer to test
    @retval        - to_t* if from_t is inherited from Y, otherwise nullptr
**/
template<class to_t, class from_t>
    requires std::derived_from<from_t, rtti_pure_base> && std::derived_from<to_t, rtti_pure_base>
to_t* rtti_cast(const std::unique_ptr<from_t>& pValue)
{
    if (pValue && pValue->template is_derived_from<to_t>())
        return static_cast<to_t*>(pValue.get());

    return nullptr;
}

/**
    @brief  Returns to_t* if from_t is inherited from Y, otherwise nullptr
    @tparam to_t       - type to cast to
    @tparam from_t     - type to cast from
    @param  pValueLink - a pointer to test
    @retval            - to_t* if from_t is inherited from Y, otherwise nullptr
**/
template<class to_t, class from_t>
    requires std::derived_from<from_t, rtti_pure_base> && std::derived_from<to_t, rtti_pure_base>
to_t* rtti_cast(const link<from_t>& pValueLink)
{
    if (auto pValue = pValueLink.lock())
        if (pValue->template is_derived_from<to_t>())
            return static_cast<to_t*>(pValue.get());

    return nullptr;
}

/**
    @brief   Returns to_t* if from_t is inherited from Y, otherwise nullptr
    @details Pointer class should contain QX_RTTI_CLASS
    @tparam  to_t   - type to cast to
    @tparam  from_t - type to cast from
    @param   value  - a value to test
    @retval         - to_t* if from_t is inherited from Y, otherwise nullptr
**/
template<class to_t, class from_t>
    requires std::derived_from<from_t, rtti_pure_base> && std::derived_from<to_t, rtti_pure_base>
to_t* rtti_cast(from_t& value)
{
    if (value.template is_derived_from<to_t>())
        return static_cast<to_t*>(&value);

    return nullptr;
}

} // namespace qx
