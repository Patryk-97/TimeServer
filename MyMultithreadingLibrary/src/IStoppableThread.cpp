#include "IStoppableThread.h"

IStoppableThread::IStoppableThread()
{
   this->t = std::thread([&] {
      {
         std::unique_lock<std::mutex> uniqueLock(this->startMutex);
         this->stoppableCondVar.wait(uniqueLock, [&]() { return this->isStarted(); });
      }
      this->run();
   });
}

IStoppableThread::~IStoppableThread()
{

}

void IStoppableThread::start(void)
{
   std::unique_lock<std::mutex> lock{ this->startMutex };
   this->isStartedFlag = true;
   this->stoppableCondVar.notify_one();
}

void IStoppableThread::stop(void)
{
   this->isStoppedFlag = true;
   if (t.joinable())
   {
      t.join();
   }
}

bool IStoppableThread::isStopped(void) const
{
   return this->isStoppedFlag.load();
}

bool IStoppableThread::isStarted(void) const
{
   return this->isStartedFlag.load();
}