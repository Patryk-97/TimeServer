#include "Communication.h"

Communication::Command Communication::getCommand(const std::string& buffer)
{
   // locals
   Communication::Command command = Communication::Command::UNDEFINED;

   if (buffer == Communication::GET_SYSTEM_TIME_REQ_STR)
   {
      command = Communication::Command::GET_SYSTEM_TIME_REQ;
   }
   else if (buffer.rfind(Communication::GET_SYSTEM_TIME_RESP_STR, 0) == 0)
   {
      command = Communication::Command::GET_SYSTEM_TIME_RESP;
   }

   return command;
}