#include "Client.h"

Client::Client()
{
   
}

Client::~Client()
{
   delete this->timeSynchronizationThread;
}

void Client::start(void)
{
   std::string ipAddress, something;
   uint16_t port;
   std::cout << "Enter ip address: ";
   std::cin >> ipAddress;
   std::cout << "Enter port: ";
   std::cin >> port;
   TcpClientSocket* client = new TcpClientSocket();
   client->init(IpProtocol::IPV4, TxProtocol::TCP);
   if (client->connect("127.0.0.1", port) == false)
   {
      std::cout << WinsockManager::getErrorMessage() << "\n";
   }

   this->timeSynchronizationThread = new TimeSynchronizationThread(client);
   this->timeSynchronizationThread->start();
   while (true)
   {
      ;
   }
}