//============================================================================
//
//!\file                       test_list_se.cpp
//
//!\brief       test single ended list qx::list_se
//!\details     ~
//
//!\author      Khrapov
//!\date        14.03.2020
//!\copyright   (c) Nick Khrapov, 2020. All right reserved.
//
//============================================================================
#include <config.h>

//V_EXCLUDE_PATH *test_list_se.cpp

#if QX_TEST_LIST_SE

#include <qx/containers/list_se.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <string>

TEST(list_se, testing)
{
    auto check_list_empty = [] (const qx::list_se<int>& l)
    {
        EXPECT_EQ(l.begin(), l.end());
        EXPECT_EQ(l.size(), 0);
        EXPECT_TRUE(l.empty());
    };

    auto check_list_full = [] (const qx::list_se<int>& l)
    {
        EXPECT_EQ(l.size(), 5);
        EXPECT_EQ(l.front(), 0);
        EXPECT_EQ(l.back(), 4);
        EXPECT_FALSE(l.empty());

        auto it = l.cbegin();
        EXPECT_EQ(*it++, 0);
        EXPECT_EQ(*it++, 1);
        EXPECT_EQ(*it++, 2);
        EXPECT_EQ(*it++, 3);
        EXPECT_EQ(*it++, 4);
    };

//---------------------------- default constructor ---------------------------

    qx::list_se<int> list0;
    check_list_empty(list0);

//----------------------- initializer_list constructor -----------------------

    qx::list_se<int> list1 { 0, 1, 2, 3, 4 };
    check_list_full(list1);

//----------------------------- copy constructor -----------------------------

    qx::list_se<int> list2(list1);
    check_list_full(list1);
    check_list_full(list2);

//----------------------------- move constructor -----------------------------

    qx::list_se<int> list3(std::move(list1));
    check_list_empty(list1);
    check_list_full(list3);

//----------------------------- fill constructor -----------------------------

    qx::list_se<int> list4(10, 7);
    EXPECT_EQ(list4.size(), 10);
    EXPECT_TRUE(std::all_of(list4.cbegin(), list4.cend(), [] (int v) { return v == 7; }));

//----------------------------------- clear ----------------------------------

    list0.clear();
    list1.clear();
    list2.clear();
    list3.clear();
    list4.clear();
    check_list_empty(list0);
    check_list_empty(list1);
    check_list_empty(list2);
    check_list_empty(list3);
    check_list_empty(list4);

//-------------------------- initializer_list assign -------------------------

    list1.assign({ 0, 1, 2, 3, 4 });
    check_list_full(list1);

//-------------------------------- copy assign -------------------------------

    list2.assign(list1);
    check_list_full(list1);
    check_list_full(list2);

//-------------------------------- move assign -------------------------------

    list3.assign(std::move(list1));
    check_list_empty(list1);
    check_list_full(list3);

//-------------------------------- fill assign -------------------------------

    list4.assign(10, 7);
    EXPECT_EQ(list4.size(), 10);
    EXPECT_TRUE(std::all_of(list4.begin(), list4.end(), [] (int v) { return v == 7; }));

//--------------------------- insert, insert_after ---------------------------

    auto it = list4.begin();

    // begin
    list4.insert(it, 0);
    list4.insert_after(it, 1);

    // middle
    ++it;
    ++it;
    ++it;
    list4.insert(it, 2);
    list4.insert_after(it, 3);

    // end
    it = list4.begin();
    for (size_t i = 0; i < list4.size() - 1; i++)
        ++it;

    list4.insert(it, 4);
    list4.insert_after(it, 5);

    it = list4.begin();
    EXPECT_EQ(list4.size(), 16);
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 4);
    EXPECT_EQ(*it++, 7);
    EXPECT_EQ(*it++, 5);

//---------------------------- erase, erase_after ----------------------------

    it = list4.begin();

    // begin
    list4.erase(it);
    it = list4.begin();
    list4.erase_after(it);

    // middle
    ++it;
    auto itTemp = it;
    list4.erase(++itTemp);
    list4.erase_after(++it);

    // end
    ++it;
    ++it;
    ++it;
    ++it;
    ++it;
    ++it;
    ++it;
    itTemp = it;
    ++itTemp;
    list4.erase(it);
    list4.erase_after(itTemp);

    EXPECT_EQ(list4.size(), 10);
    EXPECT_TRUE(std::all_of(list4.begin(), list4.end(), [] (int v) { return v == 7; }));

//--------------------------------- operator= --------------------------------

    list4 = { 3, 2, 1 };
    it = list4.begin();
    EXPECT_EQ(list4.size(), 3);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 1);

    list4 = list3;
    it = list4.begin();
    check_list_full(list4);
    check_list_full(list3);

    list4.clear();
    check_list_empty(list4);

    list4 = std::move(list3);
    check_list_full(list4);
    check_list_empty(list3);

//--------------------------- push_back, push_front --------------------------

    list4.push_front(-1);
    list4.push_back(-2);
    it = list4.begin();
    EXPECT_EQ(list4.size(), 7);
    EXPECT_EQ(*it++, -1);
    EXPECT_EQ(*it++, 0);
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(*it++, 4);
    EXPECT_EQ(*it++, -2);

//---------------------------- pop_back, pop_front ---------------------------

    list4.pop_front();
    list4.pop_back();
    check_list_full(list4);

//------------ emplace, emplace_front, emplace_back, emplace_after -----------

    qx::list_se<std::string> list5 { "0", "1" };
    EXPECT_STREQ(list5.begin()->c_str(),   "0");
    EXPECT_STREQ((++list5.begin())->c_str(), "1");

    list5.emplace_front("2");
    list5.emplace_back("3");
    list5.emplace(list5.begin(), "4");
    list5.emplace_after(list5.begin(), "5");

    auto itStr = list5.begin();
    EXPECT_EQ(list5.size(), 6);
    EXPECT_STREQ(itStr++->c_str(), "4");
    EXPECT_STREQ(itStr++->c_str(), "5");
    EXPECT_STREQ(itStr++->c_str(), "2");
    EXPECT_STREQ(itStr++->c_str(), "0");
    EXPECT_STREQ(itStr++->c_str(), "1");
    EXPECT_STREQ(itStr++->c_str(), "3");
}

#endif
