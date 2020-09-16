#include "TimeManager.h"

uint64_t TimeManager::getTimeSinceEpoch(void)
{
   return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string TimeManager::serializeTimeSinceEpoch(uint64_t timeSinceEpoch, TimeZone timeZone)
{
   // locals
   std::string serializedTime;
   std::time_t timeT;
   std::tm calendarDateTime;
   std::ostringstream oss;

   if (timeZone != TimeZone::UNDEFINED)
   {
      std::chrono::system_clock::time_point timePoint{
         std::chrono::duration_cast<std::chrono::system_clock::time_point::duration>
            (std::chrono::milliseconds(timeSinceEpoch))
      };

      timeT = std::chrono::system_clock::to_time_t(timePoint);

      if (timeZone == TimeZone::UTC)
      {
         gmtime_s(&calendarDateTime, &timeT);
      }
      else if (timeZone == TimeZone::LOCAL)
      {
         localtime_s(&calendarDateTime, &timeT);
      }

      oss << std::put_time(&calendarDateTime, TimeManager::getIso8601DateTimeFormat().data());
      serializedTime = oss.str();
   }

   return serializedTime;
}

std::string_view TimeManager::getIso8601DateTimeFormat(void)
{
   return TimeManager::ISO_8601_DATETIME_FORMAT;
}