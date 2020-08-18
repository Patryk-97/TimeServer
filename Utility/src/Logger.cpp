#include "Logger.h"

static std::mutex locker;

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::consoleLog(std::string_view line)
{
   std::lock_guard<std::mutex> lockGuard(locker);
   std::cout << line << "\n";
}

void Logger::consoleLog(std::wstring_view line)
{
   std::lock_guard<std::mutex> lockGuard(locker);
   std::wcout << line << "\n";
}