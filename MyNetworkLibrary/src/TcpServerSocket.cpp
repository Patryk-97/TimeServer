#include "TcpServerSocket.h"

TcpServerSocket::TcpServerSocket() : TcpSocket()
{
   this->socketConnections = 0;
}

TcpServerSocket::~TcpServerSocket()
{

}

bool TcpServerSocket::bind(const char* address, const uint16_t port)
{
   // locals
   bool rV = true;

   this->fillIpProtocolFamily();
   this->fillPort(port);
   rV = this->fillNetworkAddressStructure(address);

   if (true == rV &&
      ::bind(this->socketId, (sockaddr*)this->socketAddr.get(), sizeof(*this->socketAddr)) == SOCKET_ERROR)
   {
      rV = false;
   }

   return rV;
}

bool TcpServerSocket::bind(const uint16_t port)
{
   return this->bind(nullptr, port);
}

bool TcpServerSocket::listen(const int backlog)
{
   // locals
   bool rV = true;

   if (::listen(this->socketId, backlog) == SOCKET_ERROR)
   {
      rV = false;
   }

   return rV;
}

TcpClientSocket* TcpServerSocket::accept(void) const
{
   // locals
   TcpClientSocket* clientSocket = nullptr;
   std::unique_ptr<sockaddr_in> remoteClientSockAddr = std::make_unique<sockaddr_in>();
   std::unique_ptr<sockaddr_in> localClientSockAddr = std::make_unique<sockaddr_in>();
   int remoteSize = sizeof(*remoteClientSockAddr), sockAddrSize = sizeof(*localClientSockAddr);
   SOCKET clientSocketId = ::accept(this->socketId, (sockaddr*)remoteClientSockAddr.get(), &remoteSize);

   if (clientSocketId != INVALID_SOCKET &&
      ::getsockname(clientSocketId, (sockaddr*)localClientSockAddr.get(), &sockAddrSize) == 0)
   {
      clientSocket = new TcpClientSocket(clientSocketId);

      clientSocket->setLocalAddressIp(TcpSocket::convertAddressIpToStr(remoteClientSockAddr.get()).c_str());
      clientSocket->setLocalPort(TcpSocket::convertPortFromNetworkEndianness(remoteClientSockAddr.get()));
      clientSocket->setServerAddressIp(TcpSocket::convertAddressIpToStr(localClientSockAddr.get()).c_str());
      clientSocket->setPort(TcpSocket::convertPortFromNetworkEndianness(localClientSockAddr.get()));
   }

   return clientSocket;
}

uint16_t TcpServerSocket::getLocalPort(void) const
{
   return TcpSocket::convertPortFromNetworkEndianness(this->socketAddr.get());
}