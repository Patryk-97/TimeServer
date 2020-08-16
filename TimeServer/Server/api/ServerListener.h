#pragma once

#include "TcpServerSocket.h"
#include "TcpSocket.h"
#include "RandomGenerator.h"
#include "IStoppableThread.h"
#include "ClientServiceThread.h"
#include <thread>
#include <vector>

class ServerListener
{
public:
   ServerListener();
   ~ServerListener();

   void listen();

private:
   void disconnectClientCallback(ClientServiceThread* clientServiceThread);

private:
   class ServerListenerThread : public IStoppableThread
   {
   public:
      ServerListenerThread(ServerListener* serverListener) : serverListener(serverListener) {}
      ~ServerListenerThread();
      void run(void) override;
   private:
      ServerListener* serverListener {};
   } *serverListenerThread {};

   TcpServerSocket* server;
   std::vector<ClientServiceThread*> clientsThreads;
};