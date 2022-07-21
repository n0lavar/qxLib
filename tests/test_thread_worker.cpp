/**

    @file      test_thread_worker.cpp
    @author    Khrapov
    @date      17.10.2020
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#include <test_config.h>

//V_EXCLUDE_PATH *test_thread_worker.cpp

#if QX_TEST_THREAD_WORKER

    #include <qx/thread/thread_worker.h>

    #include <cmath>
    #include <memory>

constexpr size_t NUM_ITERATIONS = 1000000;
constexpr double PI_RESULT      = 3.141591653589774;



class pi_worker : public qx::thread_worker
{
public:
    double get_pi(void) const
    {
        return 4 * m_fSumm.load();
    }

private:
    virtual void thread_on_started(void) override
    {
    }

    virtual void thread_run(void) override
    {

        for (size_t i = 0; i < NUM_ITERATIONS && !thread_is_terminating(); i++)
        {
            double fExpected = m_fSumm.load();
            double fDesired  = fExpected + (std::pow(-1, i) / static_cast<double>(2 * i + 1));
            while (!m_fSumm.compare_exchange_weak(fExpected, fDesired))
                ;
        }
    }

    virtual void thread_on_stopped(void) override
    {
    }

private:
    std::atomic<double> m_fSumm = 0.f;
};



class TestThreadWorker : public ::testing::Test
{
protected:
    /* init protected members here */
    TestThreadWorker()
    {
    }

    /* called before every test */
    void SetUp()
    {
        m_pWorker     = std::make_unique<pi_worker>();
        m_fCurrentPi  = 0.f;
        m_bTerminated = false;

        EXPECT_FALSE(m_pWorker->thread_is_terminating());
        EXPECT_FALSE(m_pWorker->thread_is_running());
        EXPECT_EQ(m_pWorker->thread_get_state(), pi_worker::thread_state::inactive);

        m_pWorker->thread_start();
    }

    /* called after every test */
    void TearDown()
    {
        m_fCurrentPi = m_pWorker->get_pi();

        EXPECT_TRUE(m_pWorker->thread_is_terminating());
        EXPECT_FALSE(m_pWorker->thread_is_running());
        EXPECT_EQ(m_pWorker->thread_get_state(), pi_worker::thread_state::inactive);

        if (!m_bTerminated)
            EXPECT_DOUBLE_EQ(m_fCurrentPi, PI_RESULT);
    }

protected:
    std::unique_ptr<pi_worker> m_pWorker;
    double                     m_fCurrentPi  = 0;
    bool                       m_bTerminated = false;
};



TEST_F(TestThreadWorker, watching)
{
    while (m_pWorker->thread_is_running())
    {
        m_fCurrentPi = m_pWorker->get_pi();
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

TEST_F(TestThreadWorker, waiting)
{
    m_pWorker->thread_wait_termination();
}

TEST_F(TestThreadWorker, terminating)
{
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    m_pWorker->thread_terminate();
    m_bTerminated = true;
}

#endif
