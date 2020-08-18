#include "ClientServiceThread.h"

ClientServiceThread::~ClientServiceThread()
{
   this->stop();
   this->client->close();
   delete this->client;
}


bool ClientServiceThread::isDisconnected(void) const
{
   return this->isDisconnectedFlag;
}

void ClientServiceThread::run(void)
{
   // locals
   char recvBuff[RECV_BUFF_SIZE];
   std::string buffer, sendBuffer;
   int recvCount {}, bytesSent {};

   while (true)
   {
      if (this->isStopped())
      {
         break;
      }

      if ((recvCount = this->client->recv(recvBuff, RECV_BUFF_SIZE)) <= 0)
      {
         Logger::consoleLog("Server's side recv error!");
         break;
      }

      buffer = std::string(recvBuff, recvCount);

      //Logger::consoleLog("Client command sent to server: " + buffer);

      if (Communication::getCommand(buffer) == Communication::Command::GET_SYSTEM_TIME_REQ)
      {
         sendBuffer = Communication::GET_SYSTEM_TIME_RESP_STR.data() + " "s + std::to_string(TimeManager::getTimeSinceEpoch());
         this->client->send(sendBuffer, bytesSent);

         if (bytesSent != sendBuffer.size())
         {
            Logger::consoleLog("Server's side send error!");
            break;
         }
      }
      else
      {
         Logger::consoleLog("Invalid client's command!");
      }
   }

   Logger::consoleLog("Disconnected client");
   this->isDisconnectedFlag = true;
}