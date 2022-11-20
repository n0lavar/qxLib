/**

    @file      test_general_span.cpp
    @author    Khrapov
    @date      20.11.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/

#include <common.h>

//V_EXCLUDE_PATH *general_span.cpp

#include <qx/patterns/general_span.h>

#include <deque>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

static_assert(std::forward_iterator<qx::general_span<char>::iterator>);

template<class T, template<class> class Container>
void TestContainer()
{
    Container<std::remove_const_t<T>> container { 'a', 'b', 'c', 'd' };
    qx::general_span<T>               span(container);

    Container<std::remove_const_t<T>> newContainer;
    for (T value : span)
        newContainer.insert(newContainer.end(), value);

    EXPECT_EQ(container, newContainer);
}

TEST(general_span, container)
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

template<class T, template<class> class Container>
void TestContainerWithAdapter()
{
    using _NotT = NotT<T>;
    Container<_NotT>    container { _NotT { 'a' }, _NotT { 'b' }, _NotT { 'c' }, _NotT { 'd' } };
    qx::general_span<T> span(
        container,
        [](_NotT& notT)
        {
            return &notT.value;
        });

    Container<_NotT> newContainer;
    for (T value : span)
        newContainer.insert(newContainer.end(), _NotT { value });

    EXPECT_EQ(container, newContainer);
}

TEST(general_span, container_with_adapter)
{
    TestContainerWithAdapter<char, std::vector>();
    TestContainerWithAdapter<char, std::deque>();
    TestContainerWithAdapter<char, std::list>();
    TestContainerWithAdapter<char, std::basic_string>();
}
