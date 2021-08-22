#ifndef __HANDLERS__
#define __HANDLERS__

#include "../server/server.hpp"
#include <ctime>
#include <iostream>
#include "Shop.hpp"

class Shop_html_interface{
public:
	class FirstPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class SignupHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class SignupPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class LoginPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class AdminHandler : public RequestHandler {
	public:
	  Response *callback(Request *); 
	};

	class AdminPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *); 
	};

	class LoginHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class LogoutHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class OfferHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class HelpSellerHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class SellerHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class OfferPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class BuyerPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class WalletPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class WalletHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class ProductPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class ProductHelpHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class CartPageHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

	class PurchaseHandler : public RequestHandler {
	public:
	  Response *callback(Request *);
	};

private:
	static Shop* myshop;
};
#endif
