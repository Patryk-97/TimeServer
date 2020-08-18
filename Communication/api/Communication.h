#pragma once

#include <string>
#include <string_view>

class Communication
{
public:
   enum class Command
   {
      UNDEFINED = 0,
      GET_SYSTEM_TIME_REQ,
      GET_SYSTEM_TIME_RESP
   };

   static Command getCommand(std::string_view buffer);

   inline const static std::string_view GET_SYSTEM_TIME_REQ_STR { "GET SYSTEM TIME REQ" };
   inline const static std::string_view GET_SYSTEM_TIME_RESP_STR { "GET SYSTEM TIME RESP" };
};