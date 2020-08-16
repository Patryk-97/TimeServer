#include "ServerListener.h"

ServerListener::ServerListener()
{
   // locals
   bool bindable { false };
   RandomGenerator& randomGenerator = RandomGenerator::getInstance();

   do
   {
      this->server = new TcpServerSocket();
      bindable = this->server->bind(randomGenerator.getInteger(2000, 65535));
   } while(!bindable);
   this->serverListenerThread = new ServerListenerThread(this);
}

ServerListener::~ServerListener()
{
   this->server->close();
   delete this->server;
   delete this->serverListenerThread;
   for (auto& clientServiceThread : this->clientsThreads)
   {
      clientServiceThread->stop();
      delete clientServiceThread;
   }
   this->clientsThreads.clear();
}

void ServerListener::listen()
{
   this->serverListenerThread->start();
}

ServerListener::ServerListenerThread::~ServerListenerThread()
{
   this->stop();
}

void ServerListener::ServerListenerThread::run(void)
{
   this->serverListener->server->listen(5);
   while (true)
   {
      if (this->isStopped())
      {
         break;
      }

      TcpClientSocket* client = this->serverListener->server->accept();

      if (nullptr == client)
      {
         break;
      }

      ClientServiceThread* clientServiceThread = new ClientServiceThread(client);
      clientServiceThread->setDisconnectClientCallback(std::bind(&ServerListener::disconnectClientCallback, this->serverListener, std::placeholders::_1));
      clientServiceThread->start();
      this->serverListener->clientsThreads.push_back(clientServiceThread);
   }
}

void ServerListener::disconnectClientCallback(ClientServiceThread* clientServiceThread)
{
   this->clientsThreads.erase(std::find(this->clientsThreads.cbegin(), this->clientsThreads.cend(), clientServiceThread));
   delete clientServiceThread;
}