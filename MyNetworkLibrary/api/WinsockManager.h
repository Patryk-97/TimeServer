#pragma once

#include <winsock2.h>
#include <stdint.h>
#include <memory>
#include <string>

class WinsockManager
{
public:
   WinsockManager();
   ~WinsockManager();
   bool startup(uint16_t dllWinsockVersion);
   void cleanup(void);
   static std::string getErrorMessage(void);

private:
   std::unique_ptr<WSADATA> wsaData;
};