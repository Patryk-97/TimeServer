#include "PausableThread.h"

PausableThread::PausableThread()
{

}

PausableThread::~PausableThread()
{

}

void PausableThread::pause(void)
{
   std::unique_lock<std::mutex> uniqueLock{ this->locker };
   this->isPausedFlag = true;
   this->pausableCondVar.notify_one();
}

void PausableThread::resume(void)
{
   std::unique_lock<std::mutex> uniqueLock{ this->locker };
   this->isPausedFlag = false;
   this->pausableCondVar.notify_one();
}

void PausableThread::waitIfPaused(void)
{
   std::unique_lock<std::mutex> uniqueLock{ this->locker };
   this->pausableCondVar.wait(uniqueLock, [&] { return !this->isPausedFlag.load(); });
}