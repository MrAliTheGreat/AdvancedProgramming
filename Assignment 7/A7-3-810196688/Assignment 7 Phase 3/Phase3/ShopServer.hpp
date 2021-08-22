#ifndef __SHOP_SERVER__
#define __SHOP_SERVER__

#include "../server/server.hpp"

class ShopServer : public Server {
public:
  ShopServer(int port = 5000);
};

#endif