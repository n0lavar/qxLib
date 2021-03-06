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

#include <string>

class TestObserver1 : public qx::observer
{
    QX_RTTI_CLASS(TestObserver1, qx::observer)

public:
    static constexpr std::string_view OBSERVER = "TestObserver1: caught ";

    void EventHandler11(std::string_view svSubjectName)
    {
        sLastMsg = std::string(OBSERVER) + "EventHandler11 " + std::string(svSubjectName);
    }

    void EventHandler12(std::string_view svSubjectName)
    {
        sLastMsg = std::string(OBSERVER) + "EventHandler12 " + std::string(svSubjectName);
    }

    std::string sLastMsg;
};

class TestObserver2 : public qx::observer
{
    QX_RTTI_CLASS(TestObserver2, qx::observer)

public:

    static constexpr std::string_view OBSERVER = "TestObserver2: caught ";

    void EventHandler21(std::string_view svSubjectName)
    {
        sLastMsg = std::string(OBSERVER) + "EventHandler21 " + std::string(svSubjectName);
    }

    void EventHandler22(std::string_view svSubjectName)
    {
        sLastMsg = std::string(OBSERVER) + "EventHandler22 " + std::string(svSubjectName);
    }

    std::string sLastMsg;
};

class ISubjectForObserver1
{
public:
    virtual ~ISubjectForObserver1() = 0 {}
    virtual void EmitEvent11() = 0;
    virtual void EmitEvent12() = 0;
};

class ISubjectForObserver2
{
public:
    virtual ~ISubjectForObserver2() = 0 {}
    virtual void EmitEvent21() = 0;
    virtual void EmitEvent22() = 0;
};

class TestSubject1
    : public qx::subject
    , public ISubjectForObserver1
    , public ISubjectForObserver2
{
public:

    static constexpr std::string_view SUBJECT = "from TestSubject1";

    virtual void EmitEvent11() override
    {
        notify<TestObserver1>([](auto* pObserver)
        {
            pObserver->EventHandler11(SUBJECT);
        });
    }

    virtual void EmitEvent12() override
    {
        notify<TestObserver1>([](auto* pObserver)
        {
            pObserver->EventHandler12(SUBJECT);
        });
    }

    virtual void EmitEvent21() override
    {
        notify<TestObserver2>([](auto* pObserver)
        {
            pObserver->EventHandler21(SUBJECT);
        });
    }

    virtual void EmitEvent22() override
    {
        notify<TestObserver2>([](auto* pObserver)
        {
            pObserver->EventHandler22(SUBJECT);
        });
    }
};

class TestSubject2
    : public qx::subject
    , public ISubjectForObserver2

{
public:

    static constexpr std::string_view SUBJECT = "from TestSubject2";

    virtual void EmitEvent21() override
    {
        notify<TestObserver2>([](auto* pObserver)
        {
            pObserver->EventHandler21(SUBJECT);
        });
    }

    virtual void EmitEvent22() override
    {
        notify<TestObserver2>([](auto* pObserver)
        {
            pObserver->EventHandler22(SUBJECT);
        });
    }
};


TEST(observer, main)
{
    TestSubject1 subject1;
    EXPECT_EQ(subject1.get_num_observers(), 0);

    TestSubject2 subject2;
    EXPECT_EQ(subject2.get_num_observers(), 0);

    TestObserver1 observer1;
    observer1.attach_to(&subject1);
    EXPECT_EQ(subject1.get_num_observers(), 1);
    EXPECT_EQ(subject2.get_num_observers(), 0);

    {
        TestObserver2 observer2;
        observer2.attach_to(&subject1);
        EXPECT_EQ(subject1.get_num_observers(), 2);
        EXPECT_EQ(subject2.get_num_observers(), 0);

        observer2.attach_to(&subject2);
        EXPECT_EQ(subject1.get_num_observers(), 2);
        EXPECT_EQ(subject2.get_num_observers(), 1);

        // check reattachment protection
        observer2.attach_to(&subject2);
        EXPECT_EQ(subject1.get_num_observers(), 2);
        EXPECT_EQ(subject2.get_num_observers(), 1);

        subject1.EmitEvent11();
        EXPECT_STREQ(observer1.sLastMsg.data(), "TestObserver1: caught EventHandler11 from TestSubject1");
        EXPECT_STREQ(observer2.sLastMsg.data(), "");
        observer1.sLastMsg.clear();
        observer2.sLastMsg.clear();

        subject1.EmitEvent12();
        EXPECT_STREQ(observer1.sLastMsg.data(), "TestObserver1: caught EventHandler12 from TestSubject1");
        EXPECT_STREQ(observer2.sLastMsg.data(), "");
        observer1.sLastMsg.clear();
        observer2.sLastMsg.clear();

        subject1.EmitEvent21();
        EXPECT_STREQ(observer1.sLastMsg.data(), "");
        EXPECT_STREQ(observer2.sLastMsg.data(), "TestObserver2: caught EventHandler21 from TestSubject1");
        observer1.sLastMsg.clear();
        observer2.sLastMsg.clear();

        subject1.EmitEvent22();
        EXPECT_STREQ(observer1.sLastMsg.data(), "");
        EXPECT_STREQ(observer2.sLastMsg.data(), "TestObserver2: caught EventHandler22 from TestSubject1");
        observer1.sLastMsg.clear();
        observer2.sLastMsg.clear();

        subject2.EmitEvent21();
        EXPECT_STREQ(observer1.sLastMsg.data(), "");
        EXPECT_STREQ(observer2.sLastMsg.data(), "TestObserver2: caught EventHandler21 from TestSubject2");
        observer1.sLastMsg.clear();
        observer2.sLastMsg.clear();

        subject2.EmitEvent22();
        EXPECT_STREQ(observer1.sLastMsg.data(), "");
        EXPECT_STREQ(observer2.sLastMsg.data(), "TestObserver2: caught EventHandler22 from TestSubject2");
        observer1.sLastMsg.clear();
        observer2.sLastMsg.clear();
    }

    // check tokens detached observer2 from subjects
    EXPECT_EQ(subject1.get_num_observers(), 1);
    EXPECT_EQ(subject2.get_num_observers(), 0);

    observer1.detach_from(&subject1);
    EXPECT_EQ(subject1.get_num_observers(), 0);
    EXPECT_EQ(subject2.get_num_observers(), 0);
}

#endif