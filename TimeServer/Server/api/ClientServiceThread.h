#pragma once

#include "TcpClientSocket.h"
#include "IStoppableThread.h"
#include "TimeManager.h"
#include "Communication.h"
#include "Logger.h"

using namespace std::string_literals;

class ClientServiceThread : public IStoppableThread
{
public:
   ClientServiceThread(TcpClientSocket* client): client(client) {}
   ~ClientServiceThread();

   bool isDisconnected(void) const;
   void run(void) override;

private:
   TcpClientSocket* client;
   bool isDisconnectedFlag {};
};