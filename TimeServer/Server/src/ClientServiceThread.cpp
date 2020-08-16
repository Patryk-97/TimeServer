#include "ClientServiceThread.h"

ClientServiceThread::~ClientServiceThread()
{
   this->stop();
   delete this->client;
}

void ClientServiceThread::setDisconnectClientCallback(std::function<void(ClientServiceThread*)> disconnectClientCallback)
{
   this->disconnectClientCallback = disconnectClientCallback;
}

void ClientServiceThread::run(void)
{
   while (true)
   {
      if (this->isStopped())
      {
         break;
      }
      
   }

   this->disconnectClientCallback(this);
}