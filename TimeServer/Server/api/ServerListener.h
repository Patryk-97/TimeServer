#pragma once

#include "TcpServerSocket.h"
#include "TcpSocket.h"
#include "RandomGenerator.h"
#include "IStoppableThread.h"
#include "ClientServiceThread.h"
#include "Logger.h"
#include <thread>
#include <vector>
#include <memory>

class ServerListener
{
public:
   ServerListener();
   ~ServerListener();

   void listen(void);

private:
   void removeDisconnectedClients(void);

private:
   class ServerListenerThread : public IStoppableThread
   {
   public:
      ServerListenerThread(ServerListener* serverListener) : serverListener(serverListener) {}
      ~ServerListenerThread();
      void run(void) override;
   private:
      ServerListener* serverListener;
   } *serverListenerThread;

   TcpServerSocket* server;
   std::vector<ClientServiceThread*> clientsThreads;
   std::mutex locker;
   size_t clientsCount {};
};