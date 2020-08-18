#include "Client.h"
#include "WinsockManager.h"

#include <iostream>

#define DLL_WINSOCK_VERSION MAKEWORD(2, 2)

int main()
{
   WinsockManager winsockManager;
   if (!winsockManager.startup(DLL_WINSOCK_VERSION))
   {
      std::cout << "Winsock initialization error\n";
      return -1;
   }

   Client client{};
   client.start();
   
   winsockManager.cleanup();
   std::cin.get();
   return 0;
}