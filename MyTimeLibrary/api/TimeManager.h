#pragma once

#include <stdint.h>
#include <chrono>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

class TimeManager
{
public:
   using milliseconds = std::chrono::milliseconds;

   static uint64_t getTimeSinceEpoch(void);
   static std::string serializeTimeSinceEpoch(uint64_t timeSinceEpoch);
};