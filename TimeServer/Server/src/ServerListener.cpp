#include "ServerListener.h"

ServerListener::ServerListener()
{
   // locals
   bool bindable { false };
   RandomGenerator& randomGenerator = RandomGenerator::getInstance();

   do
   {
      this->server = new TcpServerSocket();
      this->server->init(IpProtocol::IPV4, TxProtocol::TCP);
      uint16_t port = randomGenerator.getInteger(60000, 65535);
      bindable = this->server->bind(port);
      Logger::consoleLog("bindable: "s + (bindable ? "true" : "false") + " port: "s + std::to_string(port));
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

void ServerListener::listen(void)
{
   this->serverListenerThread->start();
   while (true)
   {
      this->removeDisconnectedClients();
   }
}

void ServerListener::removeDisconnectedClients(void)
{
   {
      std::lock_guard<std::mutex> lockGuard(this->locker);
      for (size_t i = 0; i < this->clientsThreads.size(); i++)
      {
         if (this->clientsThreads[i]->isDisconnected())
         {
            delete this->clientsThreads[i];
            this->clientsThreads.erase(this->clientsThreads.begin() + i);
            i--;
         }
      }
      if (clientsCount != this->clientsThreads.size())
      {
         clientsCount = this->clientsThreads.size();
         Logger::consoleLog("Remained " + std::to_string(this->clientsThreads.size()) + " clients");
      }
   }
   std::this_thread::sleep_for(TimeManager::milliseconds(1000));
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

      Logger::consoleLog("Before new client");
      TcpClientSocket* client = this->serverListener->server->accept();
      Logger::consoleLog("New client: [" + client->getLocalAddressIp() + ":" + std::to_string(client->getLocalPort()) + "]");

      if (nullptr == client)
      {
         break;
      }

      {
         std::lock_guard<std::mutex> lockGuard(this->serverListener->locker);
         ClientServiceThread* clientServiceThread = new ClientServiceThread(client);
         clientServiceThread->start();
         this->serverListener->clientsThreads.push_back(clientServiceThread);
      }
   }
}