/**

    @file      observer.gtest.cpp
    @author    Khrapov
    @date      6.03.2021
    @copyright (c) Nick Khrapov, 2021. All right reserved.

**/
#include <common.h>

#include <qx/patterns/observer.h>

#include <memory>
#include <string>

//V_EXCLUDE_PATH *.gtest.cpp

class TestObserver
{
public:
    virtual ~TestObserver(void)              = default;
    virtual int get_num_observer(void) const = 0;

    void EventHandler1(std::string_view svSubjectName);

    void EventHandler2(std::string_view svSubjectName) const;

    std::string_view GetLastMsg() const;

    void ClearLastMsg();

private:
    mutable std::string m_sLastMsg;
};

inline void TestObserver::EventHandler1(std::string_view svSubjectName)
{
    m_sLastMsg = std::string("TestObserver") + std::to_string(get_num_observer()) + ": caught event 1 from "
                 + std::string(svSubjectName);
}

inline void TestObserver::EventHandler2(std::string_view svSubjectName) const
{
    m_sLastMsg = std::string("TestObserver") + std::to_string(get_num_observer()) + ": caught event 2 from "
                 + std::string(svSubjectName);
}

inline std::string_view TestObserver::GetLastMsg() const
{
    return m_sLastMsg;
}

inline void TestObserver::ClearLastMsg()
{
    m_sLastMsg.clear();
}

class TestObserver1 : public TestObserver
{
    virtual int get_num_observer() const override;
};

inline int TestObserver1::get_num_observer() const
{
    return 1;
}

class TestObserver2 : public TestObserver
{
    virtual int get_num_observer() const override;
};

inline int TestObserver2::get_num_observer() const
{
    return 2;
}

class TestObserver3 : public TestObserver
{
    virtual int get_num_observer() const override;
};

inline int TestObserver3::get_num_observer() const
{
    return 3;
}

class TestSubject : public qx::subject<TestObserver>
{
public:
    static constexpr std::string_view k_svSubject = "TestSubject";

    // non-const forward
    std::vector<int> EmitEvent1Forward();

    // non-const backward
    std::vector<int> EmitEvent1Backward();

    // const forward
    std::vector<int> EmitEvent2Forward() const;

    // const backward
    std::vector<int> EmitEvent2Backward() const;

    std::vector<int> EmitNotify() const;
};

inline std::vector<int> TestSubject::EmitEvent1Forward()
{
    std::vector<int> ret;
    for (auto it = begin(); it != end(); ++it)
    {
        it->EventHandler1(k_svSubject);
        ret.push_back(it->get_num_observer());
    }
    return ret;
}

inline std::vector<int> TestSubject::EmitEvent1Backward()
{
    std::vector<int> ret;
    for (auto it = rbegin(); it != rend(); ++it)
    {
        it->EventHandler1(k_svSubject);
        ret.push_back(it->get_num_observer());
    }
    return ret;
}

inline std::vector<int> TestSubject::EmitEvent2Forward() const
{
    std::vector<int> ret;
    for (auto it = cbegin(); it != cend(); ++it)
    {
        it->EventHandler2(k_svSubject);
        ret.push_back(it->get_num_observer());
    }
    return ret;
}

inline std::vector<int> TestSubject::EmitEvent2Backward() const
{
    std::vector<int> ret;
    for (auto it = crbegin(); it != crend(); ++it)
    {
        it->EventHandler2(k_svSubject);
        ret.push_back(it->get_num_observer());
    }
    return ret;
}

inline std::vector<int> TestSubject::EmitNotify() const
{
    std::vector<int> ret;
    notify(
        [&ret](TestObserver* pObserver)
        {
            pObserver->EventHandler1(k_svSubject);
            ret.push_back(pObserver->get_num_observer());
        });

    return ret;
}

class TestObserverClass : public ::testing::Test
{
protected:
    /* init protected members here */
    TestObserverClass()
    {
    }

    /* called before every test */
    void SetUp() override;

    /* called after every test */
    void TearDown() override
    {
    }

protected:
    std::unique_ptr<TestSubject>   m_pSubject;
    std::unique_ptr<TestObserver1> m_pObserver1;
    std::unique_ptr<TestObserver2> m_pObserver2;
    std::unique_ptr<TestObserver3> m_pObserver3;

    std::vector<qx::observer_token> m_Tokens;
};

inline void TestObserverClass::SetUp()
{
    m_pSubject = std::make_unique<TestSubject>();
    EXPECT_EQ(m_pSubject->get_num_observers(), 0);

    m_pObserver1 = std::make_unique<TestObserver1>();
    m_Tokens.emplace_back(m_pSubject->attach(m_pObserver1.get()));
    EXPECT_EQ(m_pSubject->get_num_observers(), 1);

    m_pObserver2 = std::make_unique<TestObserver2>();
    m_Tokens.emplace_back(m_pSubject->attach(m_pObserver2.get()));
    EXPECT_EQ(m_pSubject->get_num_observers(), 2);

    m_pObserver3 = std::make_unique<TestObserver3>();
    m_Tokens.emplace_back(m_pSubject->attach(m_pObserver3.get()));
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);
}

TEST_F(TestObserverClass, events)
{
    auto check_observers = [this](int nEvent, auto funcEmit, std::vector<int> expect)
    {
        m_pObserver1->ClearLastMsg();
        m_pObserver2->ClearLastMsg();
        m_pObserver3->ClearLastMsg();

        // check order
        EXPECT_EQ(funcEmit(), expect);

        // check msgs
        EXPECT_STREQ(
            m_pObserver1->GetLastMsg().data(),
            std::string("TestObserver1: caught event " + std::to_string(nEvent) + " from TestSubject").data());

        EXPECT_STREQ(
            m_pObserver2->GetLastMsg().data(),
            std::string("TestObserver2: caught event " + std::to_string(nEvent) + " from TestSubject").data());

        EXPECT_STREQ(
            m_pObserver3->GetLastMsg().data(),
            std::string("TestObserver3: caught event " + std::to_string(nEvent) + " from TestSubject").data());
    };

    check_observers(
        1,
        [this]()
        {
            return m_pSubject->EmitEvent1Forward();
        },
        { 1, 2, 3 });

    check_observers(
        1,
        [this]()
        {
            return m_pSubject->EmitEvent1Backward();
        },
        { 3, 2, 1 });

    check_observers(
        2,
        [this]()
        {
            return m_pSubject->EmitEvent2Forward();
        },
        { 1, 2, 3 });

    check_observers(
        2,
        [this]()
        {
            return m_pSubject->EmitEvent2Backward();
        },
        { 3, 2, 1 });

    check_observers(
        1,
        [this]()
        {
            return m_pSubject->EmitNotify();
        },
        { 1, 2, 3 });
}

TEST_F(TestObserverClass, reattachment)
{
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);

    m_Tokens.emplace_back(m_pSubject->attach(m_pObserver1.get()));
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);

    m_Tokens.emplace_back(m_pSubject->attach(m_pObserver2.get()));
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);

    m_Tokens.emplace_back(m_pSubject->attach(m_pObserver3.get()));
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);
}

TEST_F(TestObserverClass, detaching)
{
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);

    m_Tokens.erase(m_Tokens.begin());
    EXPECT_EQ(m_pSubject->get_num_observers(), 2);

    m_Tokens.erase(m_Tokens.begin());
    EXPECT_EQ(m_pSubject->get_num_observers(), 1);

    m_Tokens.erase(m_Tokens.begin());
    EXPECT_EQ(m_pSubject->get_num_observers(), 0);
}

TEST_F(TestObserverClass, observer_destructing_auto_detaching)
{
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);

    {
        TestObserver1 observer1;
        auto          token1 = m_pSubject->attach(&observer1);
        EXPECT_EQ(m_pSubject->get_num_observers(), 4);

        TestObserver2 observer2;
        auto          token2 = m_pSubject->attach(&observer2);
        EXPECT_EQ(m_pSubject->get_num_observers(), 5);

        TestObserver3 observer3;
        auto          token3 = m_pSubject->attach(&observer3);
        EXPECT_EQ(m_pSubject->get_num_observers(), 6);
    }

    EXPECT_EQ(m_pSubject->get_num_observers(), 3);
}

TEST_F(TestObserverClass, detaching_while_iterating)
{
    std::vector<int> nums;

    TestObserver1 observer1;
    m_Tokens.emplace_back(m_pSubject->attach(&observer1));
    EXPECT_EQ(m_pSubject->get_num_observers(), 4);

    TestObserver2 observer2;
    m_Tokens.emplace_back(m_pSubject->attach(&observer2));
    EXPECT_EQ(m_pSubject->get_num_observers(), 5);

    // detach all observers with number 2
    for (auto& observer : *m_pSubject)
    {
        // number of observers are constant during iterating
        // detached observers are replaced with nullptr
        EXPECT_EQ(m_pSubject->get_num_observers(), 5);
        nums.push_back(observer.get_num_observer());
        if (nums.back() == 2)
            m_Tokens[nums.size() - 1].reset();
    }

    // with destructing of last iterator all nullptrs removed
    EXPECT_EQ(m_pSubject->get_num_observers(), 3);
    EXPECT_EQ(nums, std::vector<int>({ 1, 2, 3, 1, 2 }));
}

TEST_F(TestObserverClass, subject_destructing_auto_detaching)
{
    TestObserver1 observer1;
    TestObserver1 observer2;
    TestObserver1 observer3;

    {
        TestSubject subject;

        m_Tokens.emplace_back(subject.attach(&observer1));
        EXPECT_TRUE(m_Tokens.back());

        m_Tokens.emplace_back(subject.attach(&observer2));
        EXPECT_TRUE(m_Tokens.back());

        m_Tokens.emplace_back(subject.attach(&observer3));
        EXPECT_TRUE(m_Tokens.back());
    }

    EXPECT_FALSE(**(m_Tokens.end() - 1));
    EXPECT_FALSE(**(m_Tokens.end() - 2));
    EXPECT_FALSE(**(m_Tokens.end() - 3));
}
