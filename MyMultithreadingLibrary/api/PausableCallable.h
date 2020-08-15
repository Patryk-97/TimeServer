#pragma once

#include "IStoppableCallable.h"
#include <condition_variable>
#include <mutex>

class PausableCallable : public IStoppableCallable
{
public:
   PausableCallable();
   ~PausableCallable();

   void pause(void);
   void resume(void);

protected:
   void waitIfPaused(void);

private:
   std::atomic<bool> isPausedFlag { false };
   std::condition_variable condVar;
   std::mutex lock;
};