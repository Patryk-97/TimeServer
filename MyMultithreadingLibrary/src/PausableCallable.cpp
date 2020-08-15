#include "PausableCallable.h"

PausableCallable::PausableCallable()
{

}

PausableCallable::~PausableCallable()
{

}

void PausableCallable::pause(void)
{
   std::unique_lock<std::mutex> uniqueLock{ this->lock };
   this->isPausedFlag = true;
   this->condVar.notify_one();
}

void PausableCallable::resume(void)
{
   std::unique_lock<std::mutex> uniqueLock{ this->lock };
   this->isPausedFlag = false;
   this->condVar.notify_one();
}

void PausableCallable::waitIfPaused(void)
{
   std::unique_lock<std::mutex> uniqueLock{ this->lock };
   this->condVar.wait(uniqueLock, [&] { return this->isPausedFlag.load(); });
}