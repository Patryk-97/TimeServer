#pragma once

#include "IStoppableThread.h"

class PausableThread : public IStoppableThread
{
public:
   PausableThread();
   ~PausableThread();

   void pause(void);
   void resume(void);

protected:
   void waitIfPaused(void);

private:
   std::atomic<bool> isPausedFlag { false };
   std::condition_variable pausableCondVar;
   std::mutex locker;
};