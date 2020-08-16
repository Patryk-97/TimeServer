#pragma once

#include <string>

class Communication
{
public:
   enum class Command
   {
      UNDEFINED = 0,
      GET_SYSTEM_TIME_REQ,
      GET_SYSTEM_TIME_RESP
   };

   static Command getCommand(const std::string& buffer);

   inline const static std::string GET_SYSTEM_TIME_REQ_STR { "GET SYSTEM TIME REQ" };
   inline const static std::string GET_SYSTEM_TIME_RESP_STR { "GET SYSTEM TIME RESP" };
};