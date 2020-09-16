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
   std::string_view requestCommand { Communication::GET_SYSTEM_TIME_REQ_STR };
   int sentBytes {}, recvSize {};
   char recvBuff[RECV_BUFF_SIZE];
   std::string buffer;

   while (true)
   {
      uint64_t startTime = TimeManager::getTimeSinceEpoch();
      //Logger::consoleLog("Client start time: " + std::to_string(startTime));

      if (false == this->client->send(requestCommand.data(), sentBytes) || sentBytes != requestCommand.size())
      {
         Logger::consoleLog("Client's side send error! Sent bytes: " + 
            std::to_string(sentBytes) + " requestCommand.size(): " + std::to_string(requestCommand.size()));
         break;
      }

      if((recvSize = this->client->recv(recvBuff, RECV_BUFF_SIZE)) <= 0)
      {
         Logger::consoleLog("Client's side recv error!");
         break;
      }

      buffer = std::string(recvBuff, recvSize);

      //Logger::consoleLog("Client recv this command: " + buffer);

      if (Communication::getCommand(buffer) == Communication::Command::GET_SYSTEM_TIME_RESP)
      {
         std::string timeFromServerStr = buffer.substr(Communication::GET_SYSTEM_TIME_RESP_STR.size() + 1, buffer.size());
         //Logger::consoleLog("Time from server: " + timeFromServerStr);

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

         uint64_t delta = (uint64_t)(timeFromServer + (endTime - startTime) / 2.0 - endTime);

         Logger::consoleLog("Time: " + TimeManager::serializeTimeSinceEpoch(endTime + delta, TimeManager::TimeZone::LOCAL));
         Logger::consoleLog("Delta: " + std::to_string(delta) + "ms");
      }


      std::this_thread::sleep_for(this->delay);
   }
}