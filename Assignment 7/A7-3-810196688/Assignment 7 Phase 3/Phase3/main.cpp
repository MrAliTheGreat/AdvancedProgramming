#include "handlers.hpp"
#include "ShopServer.hpp"
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand
  try{
    ShopServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("Phase3_static/404.html");
    server.get("/401", new ShowPage("Phase3_static/access_denied.html"));
    server.get("/", new Shop_html_interface::FirstPageHandler());
    server.get("/signup", new Shop_html_interface::SignupPageHandler());
    server.get("/login", new Shop_html_interface::LoginPageHandler());
    server.get("/admin", new Shop_html_interface::AdminPageHandler());
    server.get("/buyer", new Shop_html_interface::BuyerPageHandler());
    server.get("/seller", new Shop_html_interface::SellerHandler());
    server.get("/offer", new Shop_html_interface::OfferPageHandler());
    server.get("/wallet", new Shop_html_interface::WalletPageHandler());
    server.get("/product", new Shop_html_interface::ProductPageHandler());
    server.get("/cart", new Shop_html_interface::CartPageHandler());

    server.get("/logout", new Shop_html_interface::LogoutHandler());
    server.post("/signup", new Shop_html_interface::SignupHandler());
    server.post("/admin", new Shop_html_interface::AdminHandler());
    server.post("/login", new Shop_html_interface::LoginHandler());
    server.post("/offer", new Shop_html_interface::OfferHandler());
    server.post("/wallet", new Shop_html_interface::WalletHandler());
    server.post("/purchase", new Shop_html_interface::PurchaseHandler());
    server.post("/product_help", new Shop_html_interface::ProductHelpHandler());
    server.get("/back_seller", new Shop_html_interface::HelpSellerHandler());
    // server.get("/up", new ShowPage("static/upload_form.html"));
    // server.post("/up", new UploadHandler());
    // server.get("/showdetail", new RandomNumberHandler());
    // server.get("/home.png", new ShowImage("static/home.png"));
    // server.get("/", new ShowPage("static/home.html"));
    // server.get("/colors", new ColorHandler("template/colors.html"));
    server.run();
  }catch(Server::Exception e){
    cerr << e.getMessage() << endl;
  }
}