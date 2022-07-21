/**

    @file      test_observer.cpp
    @author    Khrapov
    @date      6.03.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_observer.cpp

#if QX_TEST_OBSERVER

    #include <qx/patterns/observer.h>

    #include <memory>
    #include <string>

class TestObserver
{
public:
    virtual ~TestObserver(void)              = default;
    virtual int get_num_observer(void) const = 0;

    void EventHandler1(std::string_view svSubjectName)
    {
        sLastMsg = std::string("TestObserver") + std::to_string(get_num_observer()) + ": caught event 1 from "
                   + std::string(svSubjectName);
    }

    void EventHandler2(std::string_view svSubjectName) const
    {
        sLastMsg = std::string("TestObserver") + std::to_string(get_num_observer()) + ": caught event 2 from "
                   + std::string(svSubjectName);
    }

    std::string_view GetLastMsg() const
    {
        return sLastMsg;
    }

    void ClearLastMsg()
    {
        sLastMsg.clear();
    }

private:
    mutable std::string sLastMsg;
};

class TestObserver1 : public TestObserver
{
    virtual int get_num_observer() const override
    {
        return 1;
    }
};

class TestObserver2 : public TestObserver
{
    virtual int get_num_observer() const override
    {
        return 2;
    }
};

class TestObserver3 : public TestObserver
{
    virtual int get_num_observer() const override
    {
        return 3;
    }
};

class TestSubject : public qx::subject<TestObserver>
{
public:
    static constexpr std::string_view SUBJECT = "TestSubject";

    // non-const forward
    std::vector<int> EmitEvent1Forward()
    {
        std::vector<int> ret;
        for (auto it = begin(); it != end(); ++it)
        {
            it->EventHandler1(SUBJECT);
            ret.push_back(it->get_num_observer());
        }
        return ret;
    }

    // non-const backward
    std::vector<int> EmitEvent1Backward()
    {
        std::vector<int> ret;
        for (auto it = rbegin(); it != rend(); ++it)
        {
            it->EventHandler1(SUBJECT);
            ret.push_back(it->get_num_observer());
        }
        return ret;
    }

    // const forward
    std::vector<int> EmitEvent2Forward() const
    {
        std::vector<int> ret;
        for (auto it = cbegin(); it != cend(); ++it)
        {
            it->EventHandler2(SUBJECT);
            ret.push_back(it->get_num_observer());
        }
        return ret;
    }

    // const backward
    std::vector<int> EmitEvent2Backward() const
    {
        std::vector<int> ret;
        for (auto it = crbegin(); it != crend(); ++it)
        {
            it->EventHandler2(SUBJECT);
            ret.push_back(it->get_num_observer());
        }
        return ret;
    }

    std::vector<int> EmitNotify() const
    {
        std::vector<int> ret;
        notify(
            [&ret](TestObserver* pObserver)
            {
                pObserver->EventHandler1(SUBJECT);
                ret.push_back(pObserver->get_num_observer());
            });

        return ret;
    }
};

class TestObserverClass : public ::testing::Test
{
protected:
    /* init protected members here */
    TestObserverClass()
    {
    }

    /* called before every test */
    void SetUp() override
    {
        pSubject = std::make_unique<TestSubject>();
        EXPECT_EQ(pSubject->get_num_observers(), 0);

        pObserver1 = std::make_unique<TestObserver1>();
        tokens.emplace_back(pSubject->attach(pObserver1.get()));
        EXPECT_EQ(pSubject->get_num_observers(), 1);

        pObserver2 = std::make_unique<TestObserver2>();
        tokens.emplace_back(pSubject->attach(pObserver2.get()));
        EXPECT_EQ(pSubject->get_num_observers(), 2);

        pObserver3 = std::make_unique<TestObserver3>();
        tokens.emplace_back(pSubject->attach(pObserver3.get()));
        EXPECT_EQ(pSubject->get_num_observers(), 3);
    }

    /* called after every test */
    void TearDown() override
    {
    }

protected:
    std::unique_ptr<TestSubject>   pSubject;
    std::unique_ptr<TestObserver1> pObserver1;
    std::unique_ptr<TestObserver2> pObserver2;
    std::unique_ptr<TestObserver3> pObserver3;

    std::vector<qx::observer_token> tokens;
};

TEST_F(TestObserverClass, events)
{
    auto check_observers = [this](int nEvent, auto funcEmit, std::vector<int> expect)
    {
        pObserver1->ClearLastMsg();
        pObserver2->ClearLastMsg();
        pObserver3->ClearLastMsg();

        // check order
        EXPECT_EQ(funcEmit(), expect);

        // check msgs
        EXPECT_STREQ(
            pObserver1->GetLastMsg().data(),
            std::string("TestObserver1: caught event " + std::to_string(nEvent) + " from TestSubject").data());

        EXPECT_STREQ(
            pObserver2->GetLastMsg().data(),
            std::string("TestObserver2: caught event " + std::to_string(nEvent) + " from TestSubject").data());

        EXPECT_STREQ(
            pObserver3->GetLastMsg().data(),
            std::string("TestObserver3: caught event " + std::to_string(nEvent) + " from TestSubject").data());
    };

    check_observers(
        1,
        [this]()
        {
            return pSubject->EmitEvent1Forward();
        },
        { 1, 2, 3 });

    check_observers(
        1,
        [this]()
        {
            return pSubject->EmitEvent1Backward();
        },
        { 3, 2, 1 });

    check_observers(
        2,
        [this]()
        {
            return pSubject->EmitEvent2Forward();
        },
        { 1, 2, 3 });

    check_observers(
        2,
        [this]()
        {
            return pSubject->EmitEvent2Backward();
        },
        { 3, 2, 1 });

    check_observers(
        1,
        [this]()
        {
            return pSubject->EmitNotify();
        },
        { 1, 2, 3 });
}

TEST_F(TestObserverClass, reattachment)
{
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    tokens.emplace_back(pSubject->attach(pObserver1.get()));
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    tokens.emplace_back(pSubject->attach(pObserver2.get()));
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    tokens.emplace_back(pSubject->attach(pObserver3.get()));
    EXPECT_EQ(pSubject->get_num_observers(), 3);
}

TEST_F(TestObserverClass, detaching)
{
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    tokens.erase(tokens.begin());
    EXPECT_EQ(pSubject->get_num_observers(), 2);

    tokens.erase(tokens.begin());
    EXPECT_EQ(pSubject->get_num_observers(), 1);

    tokens.erase(tokens.begin());
    EXPECT_EQ(pSubject->get_num_observers(), 0);
}

TEST_F(TestObserverClass, observer_destructing_auto_detaching)
{
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    {
        TestObserver1 observer1;
        auto          token1 = pSubject->attach(&observer1);
        EXPECT_EQ(pSubject->get_num_observers(), 4);

        TestObserver2 observer2;
        auto          token2 = pSubject->attach(&observer2);
        EXPECT_EQ(pSubject->get_num_observers(), 5);

        TestObserver3 observer3;
        auto          token3 = pSubject->attach(&observer3);
        EXPECT_EQ(pSubject->get_num_observers(), 6);
    }

    EXPECT_EQ(pSubject->get_num_observers(), 3);
}

TEST_F(TestObserverClass, detaching_while_iterating)
{
    std::vector<int> nums;

    TestObserver1 observer1;
    tokens.emplace_back(pSubject->attach(&observer1));
    EXPECT_EQ(pSubject->get_num_observers(), 4);

    TestObserver2 observer2;
    tokens.emplace_back(pSubject->attach(&observer2));
    EXPECT_EQ(pSubject->get_num_observers(), 5);

    // detach all observers with number 2
    for (auto& observer : *pSubject)
    {
        // number of observers are constant during iterating
        // detached observers are replaced with nullptr
        EXPECT_EQ(pSubject->get_num_observers(), 5);
        nums.push_back(observer.get_num_observer());
        if (nums.back() == 2)
            tokens[nums.size() - 1].reset();
    }

    // with destructing of last iterator all nullptrs removed
    EXPECT_EQ(pSubject->get_num_observers(), 3);
    EXPECT_EQ(nums, std::vector<int>({ 1, 2, 3, 1, 2 }));
}

TEST_F(TestObserverClass, subject_destructing_auto_detaching)
{
    TestObserver1 observer1;
    TestObserver1 observer2;
    TestObserver1 observer3;

    {
        TestSubject subject;

        tokens.emplace_back(subject.attach(&observer1));
        EXPECT_TRUE(tokens.back());

        tokens.emplace_back(subject.attach(&observer2));
        EXPECT_TRUE(tokens.back());

        tokens.emplace_back(subject.attach(&observer3));
        EXPECT_TRUE(tokens.back());
    }

    EXPECT_FALSE(**(tokens.end() - 1));
    EXPECT_FALSE(**(tokens.end() - 2));
    EXPECT_FALSE(**(tokens.end() - 3));
}

#endif
