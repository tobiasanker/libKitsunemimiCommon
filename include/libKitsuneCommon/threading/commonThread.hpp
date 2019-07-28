/**
 *  @file    commonThread.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef COMMONTHREAD_HPP
#define COMMONTHREAD_HPP

#include <mutex>
#include <condition_variable>
#include <thread>
#include <pthread.h>
#include <vector>

namespace Kitsune
{
class CommonDataBuffer;

class CommonThread
{
public:
    CommonThread(int coreId = -1);
    virtual ~CommonThread();

    bool start();
    void stop();
    bool waitForFinish();

    void continueThread();
    void initBlockThread();

    bool isActive() const;
    bool bindThreadToCore(const int coreId);

protected:
    std::thread* m_thread = nullptr;

    bool m_abort = false;
    bool m_block = false;
    bool m_active = false;

    int m_coreId = -1;

    std::mutex m_mutex;
    std::mutex m_cvMutex;
    std::condition_variable m_cv;

    void blockThread();
    void sleepThread(const uint32_t microSeconds);

    void mutexLock();
    void mutexUnlock();

    virtual void run() = 0;
};

} // namespace Kitsune

#endif // COMMONTHREAD_HPP
