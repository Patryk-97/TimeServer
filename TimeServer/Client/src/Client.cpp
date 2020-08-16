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
   std::cout << client->connect(ipAddress.c_str(), port) ? "true\n" : "false\n";
   client->close();
   delete client;
}