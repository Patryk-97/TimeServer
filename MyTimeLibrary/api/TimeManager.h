#pragma once

#include <stdint.h>
#include <chrono>
#include <string>
//#include <ctime>
#include <time.h>
#include <sstream>
#include <iomanip>

class TimeManager
{
public:
   using milliseconds = std::chrono::milliseconds;
   using seconds = std::chrono::seconds;

   enum class TimeZone
   {
      UNDEFINED = 0,
      UTC,
      LOCAL
   };

   static uint64_t getTimeSinceEpoch(void);
   static std::string serializeTimeSinceEpoch(uint64_t timeSinceEpoch, TimeZone timeZone);
   static std::string_view getIso8601DateTimeFormat(void);
private:
   inline static const std::string_view ISO_8601_DATETIME_FORMAT = "%Y-%m-%dT%H:%M:%SZ";
};