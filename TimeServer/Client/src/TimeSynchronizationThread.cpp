#include "TimeSynchronizationThread.h"

TimeSynchronizationThread::~TimeSynchronizationThread()
{
   this->client->close();
   delete this->client;
   this->stop();
}

void TimeSynchronizationThread::run(void)
{
   // locals
   const std::string& requestCommand = Communication::GET_SYSTEM_TIME_REQ_STR;
   int sentBytes {}, recvSize {};
   char recvBuff[RECV_BUFF_SIZE];
   std::string buffer;

   while (true)
   {
      uint64_t startTime = TimeManager::getTimeSinceEpoch();

      if (false == (sentBytes = this->client->send(requestCommand, sentBytes)) || sentBytes != requestCommand.size())
      {
         break;
      }

      if((recvSize = this->client->recv(recvBuff, RECV_BUFF_SIZE)) <= 0)
      {
         break;
      }

      buffer = std::string(recvBuff, recvSize);

      if (Communication::getCommand(buffer) == Communication::Command::GET_SYSTEM_TIME_RESP)
      {
         std::string timeFromServerStr = buffer.substr(Communication::GET_SYSTEM_TIME_RESP_STR.size() + 1, buffer.size());
         uint64_t timeFromServer{};

         try
         {
            timeFromServer = std::stoull(timeFromServerStr);
         }
         catch (...)
         {
            break;
         }

         uint64_t endTime = TimeManager::getTimeSinceEpoch();

         uint64_t delta = (uint64_t)(timeFromServer + (endTime - startTime) / 2.0 - timeFromServer);

         std::cout << "Time: " + TimeManager::serializeTimeSinceEpoch(endTime + delta) << "\n";
         std::cout << "Delta: " + std::to_string(delta) << "ms";
      }


      std::this_thread::sleep_for(this->delay);
   }
}