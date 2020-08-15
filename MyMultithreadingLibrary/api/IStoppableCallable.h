#pragma once

#include <atomic>

class IStoppableCallable
{
public:
   IStoppableCallable();
   virtual ~IStoppableCallable();

   void operator()(void);

   // Method to implement
   virtual void run() = 0;

   void stop(void);
   bool isStopped(void);

private:
   std::atomic<bool> isStoppedFlag { false };
};