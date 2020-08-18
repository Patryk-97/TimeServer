#pragma once

#include <iostream>
#include <string_view>
#include <mutex>

class Logger
{
public:
   Logger();
   virtual ~Logger();

   static void consoleLog(std::string_view line);
   static void consoleLog(std::wstring_view line);
};