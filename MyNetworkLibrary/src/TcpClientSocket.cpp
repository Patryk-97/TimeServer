#include "TcpClientSocket.h"

TcpClientSocket::TcpClientSocket() : TcpSocket()
{
   this->localSocketAddr = std::make_unique<sockaddr_in>();
   this->localPort = 0;
   this->port = 0;
}

TcpClientSocket::TcpClientSocket(SOCKET socketId) : TcpClientSocket()
{
   this->socketId = socketId;
}

TcpClientSocket::~TcpClientSocket()
{

}

void TcpClientSocket::reset(void)
{
   TcpSocket::reset();
   this->socketAddr.reset(new sockaddr_in());
   this->localPort = 0;
   this->port = 0;
   this->serverAddressIp = "";
   this->localAddressIp = "";
}

bool TcpClientSocket::connect(const char* address, const uint16_t port)
{
   // locals
   bool rV = true;
   int sockAddrSize = sizeof(*this->localSocketAddr);

   this->fillIpProtocolFamily();
   this->fillPort(port);
   rV = this->fillNetworkAddressStructure(address);

   if (true == rV &&
      ::connect(this->socketId, (sockaddr*)this->socketAddr.get(), sizeof(*this->socketAddr)) == SOCKET_ERROR)
   {
      rV = false;
   }

   if (true == rV &&
      ::getsockname(this->socketId, (sockaddr*)this->localSocketAddr.get(), &sockAddrSize) == SOCKET_ERROR)
   {
      rV = false;
   }

   if (true == rV)
   {
      this->port = port;
      this->serverAddressIp = TcpSocket::convertAddressIpToStr(this->socketAddr.get());
      this->localPort = TcpSocket::convertPortFromNetworkEndianness(this->localSocketAddr.get());
      this->localAddressIp = TcpSocket::convertAddressIpToStr(this->localSocketAddr.get());
   }

   return rV;
}

void TcpClientSocket::setLocalPort(uint16_t localPort)
{
   this->localPort = localPort;
}

uint16_t TcpClientSocket::getLocalPort(void) const
{
   return this->localPort;
}

void TcpClientSocket::setPort(uint16_t port)
{
   this->port = port;
}

uint16_t TcpClientSocket::getPort(void) const
{
   return this->port;
}

void TcpClientSocket::setLocalAddressIp(const char* localAddressIp)
{
   this->localAddressIp = localAddressIp;
}

std::string TcpClientSocket::getLocalAddressIp(void) const
{
   return this->localAddressIp;
}

void TcpClientSocket::setServerAddressIp(const char* serverAddressIp)
{
   this->serverAddressIp = serverAddressIp;
}

std::string TcpClientSocket::getServerAddressIp(void) const
{
   return this->serverAddressIp;
}