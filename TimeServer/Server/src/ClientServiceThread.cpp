#include "ClientServiceThread.h"

ClientServiceThread::~ClientServiceThread()
{
   this->stop();
   this->client->close();
   delete this->client;
}

void ClientServiceThread::setDisconnectClientCallback(std::function<void(ClientServiceThread*)> disconnectClientCallback)
{
   this->disconnectClientCallback = disconnectClientCallback;
}

void ClientServiceThread::run(void)
{
   // locals
   char recvBuff[RECV_BUFF_SIZE];
   std::string buffer;
   int recvCount {};

   while (true)
   {
      if (this->isStopped())
      {
         break;
      }

      recvCount = this->client->recv(recvBuff, RECV_BUFF_SIZE);

      if (recvCount <= 0)
      {
         break;
      }

      buffer = std::string(recvCount, recvCount);

      if (Communication::getCommand(buffer) == Communication::Command::GET_SYSTEM_TIME_REQ)
      {
         std::string sendBuffer = Communication::GET_SYSTEM_TIME_RESP_STR + " "s + std::to_string(TimeManager::getTimeSinceEpoch());
         int bytesSend {};
         this->client->send(sendBuffer, bytesSend);

         if (bytesSend != sendBuffer.size())
         {
            break;
         }
      }
      else
      {
         ;
      }
   }

   this->disconnectClientCallback(this);
}