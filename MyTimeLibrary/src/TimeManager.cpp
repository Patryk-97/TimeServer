#include "TimeManager.h"

uint64_t TimeManager::getTimeSinceEpoch(void)
{
   return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string TimeManager::serializeTimeSinceEpoch(uint64_t timeSinceEpoch)
{
   std::chrono::system_clock::time_point timePoint {
      std::chrono::duration_cast<std::chrono::system_clock::time_point::duration>
         (std::chrono::milliseconds(timeSinceEpoch)) 
   };

   std::time_t tt = std::chrono::system_clock::to_time_t(timePoint);
   std::tm tm;
   gmtime_s(&tm, &tt);
   //std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
   std::ostringstream ss;
   ss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
   return ss.str();

}