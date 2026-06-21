/**

    @file      generic_span.gtest.cpp
    @author    Khrapov
    @date      20.11.2022
    @copyright (c) Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

#include <qx/patterns/generic_span.h>

#include <deque>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

static_assert(std::forward_iterator<qx::generic_span<char>::iterator>);

template<class T, template<class...> class container_t>
void TestContainer()
{
    container_t<std::remove_const_t<T>> container { 'a', 'b', 'c', 'd' };
    qx::generic_span<T>                 span;
    EXPECT_TRUE(span.empty());
    span = container;
    EXPECT_FALSE(span.empty());

    container_t<std::remove_const_t<T>> newContainer;
    for (T value : span)
        newContainer.insert(newContainer.end(), value);

    auto it1 = std::ranges::find(span, 'b');
    EXPECT_TRUE(it1);
    EXPECT_EQ(*it1, 'b');

    auto it2 = std::ranges::find(span, 'u');
    EXPECT_FALSE(it2);

    EXPECT_EQ(container, newContainer);
}

TEST(generic_span, container)
{
    TestContainer<char, std::vector>();
    TestContainer<char, std::deque>();
    TestContainer<char, std::list>();
    TestContainer<char, std::basic_string>();

    TestContainer<const char, std::vector>();
    TestContainer<const char, std::deque>();
    TestContainer<const char, std::list>();
    TestContainer<const char, std::basic_string>();
}

template<class T>
struct NotT
{
    T value;

    auto operator<=>(const NotT&) const = default;
};

template<class T>
struct std::hash<NotT<T>>
{
    size_t operator()(const NotT<T>& value) const noexcept
    {
        return std::hash<T>()(value.value);
    }
};

template<class T, template<class...> class container_t>
void TestContainerWithAdapter()
{
    using _NotT = NotT<T>;
    container_t<_NotT>  container { _NotT { 'a' }, _NotT { 'b' }, _NotT { 'c' }, _NotT { 'd' } };
    qx::generic_span<T> span(
        container,
        [](_NotT& notT) -> T&
        {
            return notT.value;
        });
    EXPECT_FALSE(span.empty());

    container_t<_NotT> newContainer;
    for (qx::copy_qualifiers_t<decltype(container), T>& value : span)
        newContainer.insert(newContainer.end(), _NotT { value });

    auto it1 = std::ranges::find(span, 'b');
    EXPECT_TRUE(it1);
    EXPECT_EQ(*it1, 'b');

    auto it2 = std::ranges::find(span, 'u');
    EXPECT_FALSE(it2);

    EXPECT_EQ(container, newContainer);
}

TEST(generic_span, container_with_adapter)
{
    TestContainerWithAdapter<char, std::vector>();
    TestContainerWithAdapter<char, std::deque>();
    TestContainerWithAdapter<char, std::list>();
    TestContainerWithAdapter<char, std::basic_string>();
}
