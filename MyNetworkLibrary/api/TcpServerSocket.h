#pragma once

#define RECV_BUFF_SIZE 4096

#include "TcpSocket.h"
#include "TcpClientSocket.h"
#include "WinsockManager.h"

#include <memory>

class TcpServerSocket : public TcpSocket
{
public:
   TcpServerSocket();
   ~TcpServerSocket();
   bool bind(const char* address, const uint16_t port);
   bool listen(const int backlog);
   TcpClientSocket* accept(void) const;
   uint16_t getLocalPort(void) const;

private:
   uint8_t socketConnections;
};