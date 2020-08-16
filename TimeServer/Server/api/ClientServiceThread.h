#pragma once

#include "TcpClientSocket.h"
#include "IStoppableThread.h"

#include <functional>

class ClientServiceThread : public IStoppableThread
{
public:
   ClientServiceThread(TcpClientSocket* client): client(client) {}
   ~ClientServiceThread();

   void setDisconnectClientCallback(std::function<void(ClientServiceThread*)> disconnectClientCallback);

   void run(void) override;

private:
   TcpClientSocket* client {};
   std::function<void(ClientServiceThread*)> disconnectClientCallback;
};