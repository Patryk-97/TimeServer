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
      std::cout << "bindable: " << (bindable ? "true" : "false") << " port: " << port << "\n";
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
   while (true)
   {
      ;
   }
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