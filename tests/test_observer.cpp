//==============================================================================
//
//!\file                       test_observer.cpp
//
//!\brief       Tests for qx::observer
//!\details     ~
//
//!\author      Khrapov
//!\date        6.03.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#include <test_config.h>

//V_EXCLUDE_PATH *test_observer.cpp

#if QX_TEST_OBSERVER

#include <qx/observer.h>

#include <memory>
#include <string>

class TestObserver : public qx::observer
{
public:

    virtual int get_num_observer() const = 0;

    void EventHandler1(std::string_view svSubjectName)
    {
        sLastMsg = std::string("TestObserver")
            + std::to_string(get_num_observer())
            + ": caught event 1 from "
            + std::string(svSubjectName);
    }

    void EventHandler2(std::string_view svSubjectName) const
    {
        sLastMsg = std::string("TestObserver")
            + std::to_string(get_num_observer())
            + ": caught event 2 from "
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
        pObserver1->attach_to(pSubject.get());
        EXPECT_EQ(pSubject->get_num_observers(), 1);

        pObserver2 = std::make_unique<TestObserver2>();
        pObserver2->attach_to(pSubject.get());
        EXPECT_EQ(pSubject->get_num_observers(), 2);

        pObserver3 = std::make_unique<TestObserver3>();
        pObserver3->attach_to(pSubject.get());
        EXPECT_EQ(pSubject->get_num_observers(), 3);
    }

    /* called after every test */
    void TearDown() override
    {
    }

protected:

    std::unique_ptr<TestSubject> pSubject;
    std::unique_ptr<TestObserver1> pObserver1;
    std::unique_ptr<TestObserver2> pObserver2;
    std::unique_ptr<TestObserver3> pObserver3;
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

    check_observers(1, [this](){ return pSubject->EmitEvent1Forward(); },  { 1, 2, 3 });
    check_observers(1, [this](){ return pSubject->EmitEvent1Backward(); }, { 3, 2, 1 });
    check_observers(2, [this](){ return pSubject->EmitEvent2Forward(); },  { 1, 2, 3 });
    check_observers(2, [this](){ return pSubject->EmitEvent2Backward(); }, { 3, 2, 1 });
}

TEST_F(TestObserverClass, reattachment)
{
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    pObserver1->attach_to(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    pObserver2->attach_to(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    pObserver3->attach_to(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 3);
}

TEST_F(TestObserverClass, detaching)
{
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    pObserver1->detach_from(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 2);

    pObserver2->detach_from(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 1);

    pObserver3->detach_from(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 0);
}

TEST_F(TestObserverClass, detaching_all)
{
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    TestSubject subject2;
    pObserver1->attach_to(&subject2);
    pObserver2->attach_to(&subject2);
    EXPECT_EQ(subject2.get_num_observers(), 2);

    pObserver1->detach_from_all();
    EXPECT_EQ(pSubject->get_num_observers(), 2);
    EXPECT_EQ(subject2.get_num_observers(), 1);

    pObserver2->detach_from_all();
    EXPECT_EQ(pSubject->get_num_observers(), 1);
    EXPECT_EQ(subject2.get_num_observers(), 0);

    pObserver3->detach_from_all();
    EXPECT_EQ(pSubject->get_num_observers(), 0);
    EXPECT_EQ(subject2.get_num_observers(), 0);
}

TEST_F(TestObserverClass, observer_destructing_auto_detaching)
{
    EXPECT_EQ(pSubject->get_num_observers(), 3);

    {
        TestObserver1 observer1;
        observer1.attach_to(pSubject.get());
        EXPECT_EQ(pSubject->get_num_observers(), 4);

        TestObserver2 observer2;
        observer2.attach_to(pSubject.get());
        EXPECT_EQ(pSubject->get_num_observers(), 5);

        TestObserver3 observer3;
        observer3.attach_to(pSubject.get());
        EXPECT_EQ(pSubject->get_num_observers(), 6);
    }

    EXPECT_EQ(pSubject->get_num_observers(), 3);
}

TEST_F(TestObserverClass, detaching_while_iterating)
{
    std::vector<int> nums;

    TestObserver1 observer1;
    observer1.attach_to(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 4);

    TestObserver2 observer2;
    observer2.attach_to(pSubject.get());
    EXPECT_EQ(pSubject->get_num_observers(), 5);

    // detach all observers with number 2
    for (auto& observer : *pSubject)
    {
        // number of observers are constant during iterating
        // detached observers are replaced with nullptr
        EXPECT_EQ(pSubject->get_num_observers(), 5);
        nums.push_back(observer.get_num_observer());
        if (nums.back() == 2)
            observer.detach_from(pSubject.get());
    }

    // with destructing of last iterator all nullptrs removed
    EXPECT_EQ(pSubject->get_num_observers(), 3);
    EXPECT_EQ(nums, std::vector<int>({ 1, 2, 3, 1, 2 }));
}

TEST_F(TestObserverClass, subject_destructing_auto_detaching)
{
    {
        TestSubject subject;

        pObserver1->attach_to(&subject);
        EXPECT_EQ(pObserver1->get_num_subjects_attached_to(), 2);

        pObserver2->attach_to(&subject);
        EXPECT_EQ(pObserver2->get_num_subjects_attached_to(), 2);

        pObserver3->attach_to(&subject);
        EXPECT_EQ(pObserver3->get_num_subjects_attached_to(), 2);
    }

    EXPECT_EQ(pObserver1->get_num_subjects_attached_to(), 1);
    EXPECT_EQ(pObserver2->get_num_subjects_attached_to(), 1);
    EXPECT_EQ(pObserver3->get_num_subjects_attached_to(), 1);
}

#endif
