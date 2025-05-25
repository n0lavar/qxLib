/**

    @file      test_smart_ptr_ref_adapter.cpp
    @author    Khrapov
    @date      25.05.2025
    @copyright © Nick Khrapov, 2025. All right reserved.

**/
#include <common.h>

#include <qx/smart_ptr/shared_ref.h>
#include <qx/smart_ptr/unique_ref.h>

//V_EXCLUDE_PATH *test_smart_ptr_ref_adapter.cpp

class test_class
{
public:
    test_class(std::string data) : m_Data(std::move(data))
    {
        ++m_ObjectsAlive;
    }

    ~test_class()
    {
        --m_ObjectsAlive;
    }

    const std::string& get_data() const
    {
        return m_Data;
    }

    static size_t get_objects_alive()
    {
        return m_ObjectsAlive;
    }

private:
    std::string          m_Data;
    inline static size_t m_ObjectsAlive = 0;
};

template<template<class, class...> class pointer_t, class T, class... args_t>
static void test_adapter(
    qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...> object1,
    qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...> object2)
{
    EXPECT_EQ(test_class::get_objects_alive(), 2);

    std::string dataObject1 = object1->get_data();
    std::string dataObject2 = object2.get().get_data();

    const size_t object1Hash        = std::hash<qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...>>()(object1);
    const size_t object1PointerHash = std::hash<T*>()(&object1.get());
    EXPECT_EQ(object1Hash, object1PointerHash);

    const size_t object2Hash        = std::hash<qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...>>()(object2);
    const size_t object2PointerHash = std::hash<T*>()(&object2.get());
    EXPECT_EQ(object2Hash, object2PointerHash);

    EXPECT_FALSE(dataObject1.empty());
    EXPECT_FALSE(dataObject2.empty());

    object1.swap(object2);
    EXPECT_EQ(test_class::get_objects_alive(), 2);
    EXPECT_EQ(dataObject1, object2->get_data());
    EXPECT_EQ(dataObject2, object1->get_data());

    std::swap(object1, object2);
    EXPECT_EQ(test_class::get_objects_alive(), 2);
    EXPECT_EQ(dataObject1, object1->get_data());
    EXPECT_EQ(dataObject2, object2->get_data());

#if 0 // should not compile (ptr constructor)
    pointer_t<T, args_t...> ptr1;
    qx::details::smart_ptr_ref_adapter<pointer_t, T, args_t...> ref(std::move(ptr1));
#endif

#if 0 // should not compile (ptr assignment)
    pointer_t<T, args_t...> ptr2;
    object1 = std::move(ptr2);
#endif

#if 0 // should not compile (ptr resetting)
    pointer_t<T, args_t...> ptr3;
    object1.reset(std::move(ptr3));
#endif

#if 0 // should not compile for unique_ref (ref resetting)
    object1.reset(object2);
#endif

    object1.reset(std::move(object2));
    EXPECT_EQ(dataObject2, object1->get_data());
    EXPECT_EQ(test_class::get_objects_alive(), 1);
}

static void test_pointer(auto Factory)
{
    EXPECT_EQ(test_class::get_objects_alive(), 0);

    auto object1 = Factory("1");
    EXPECT_EQ(test_class::get_objects_alive(), 1);

    auto object2 = Factory("2");
    EXPECT_EQ(test_class::get_objects_alive(), 2);

    test_adapter(std::move(object1), std::move(object2));
    EXPECT_EQ(test_class::get_objects_alive(), 0);
}

static qx::unique_ref<test_class> create_unique_ref(const std::string& suffix)
{
    return qx::make_unique_ref<test_class>("test_class_unique_ref_type " + suffix);
}

static void test_class_deleter(const test_class* testClass)
{
    delete testClass;
}

static qx::unique_ref<test_class, decltype(&test_class_deleter)> create_unique_ref_deleter(const std::string& suffix)
{
    return qx::make_unique_ref_with_deleter<test_class>(
        test_class_deleter,
        "test_class_unique_ref_deleter_type " + suffix);
}

static qx::shared_ref<test_class> create_shared_ref(const std::string& suffix)
{
    return qx::make_shared_ref<test_class>("test_class_shared_ref_type " + suffix);
}

TEST(smart_ptr_ref_adapter, unique_ref)
{
    test_pointer(create_unique_ref);
}

TEST(smart_ptr_ref_adapter, unique_ref_deleter)
{
    test_pointer(create_unique_ref_deleter);
}

TEST(smart_ptr_ref_adapter, shared_ref)
{
    test_pointer(create_shared_ref);
}
