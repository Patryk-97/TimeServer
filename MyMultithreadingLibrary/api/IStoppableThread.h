#pragma once

#include <atomic>
#include <thread>
#include <condition_variable>
#include <mutex>

class IStoppableThread
{
public:
   IStoppableThread();
   virtual ~IStoppableThread();

   // Method to implement
   virtual void run() = 0;

   void start(void);
   void stop(void);
   bool isStopped(void) const;
   bool isStarted(void) const;

private:
   std::atomic<bool> isStoppedFlag { false }, isStartedFlag { false };
   std::thread t;
   std::condition_variable stoppableCondVar;
   std::mutex startMutex;
};