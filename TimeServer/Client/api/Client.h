#pragma once

#include "TimeSynchronizationThread.h"
#include "TcpClientSocket.h"
#include "WinsockManager.h"

#include <iostream>

class Client
{
public:
   Client();
   ~Client();

   void start(void);

private:
   TimeSynchronizationThread* timeSynchronizationThread{};
};