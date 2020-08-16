#include "IStoppableThread.h"

IStoppableThread::IStoppableThread()
{

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