#include "ServerListener.h"
#include "WinsockManager.h"

#include <string_view>
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

   ServerListener serverListener;
   serverListener.listen();

   winsockManager.cleanup();
   std::cin.get();
   return 0;
}