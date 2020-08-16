#pragma once

#include "TcpClientSocket.h"
#include "IStoppableThread.h"
#include "Communication.h"
#include "TimeManager.h"

#include <iostream>

class TimeSynchronizationThread : public IStoppableThread
{
public:
   TimeSynchronizationThread(TcpClientSocket* client) : client(client), delay(TimeManager::milliseconds(0)) {}
   ~TimeSynchronizationThread();

   void run(void) override;

private:
   TcpClientSocket* client {};
   TimeManager::milliseconds delay;
};