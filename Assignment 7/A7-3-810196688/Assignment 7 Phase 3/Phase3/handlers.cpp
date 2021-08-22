#include "handlers.hpp"
#include "Program_errors.hpp"
#include <sstream>
#include <string>
#include <vector>

#define NUM_ROWS_HEADER 1

using namespace std;

Shop* Shop_html_interface::myshop = new Shop();

std::vector<std::string> extractor_file(std::string file_context){
  std::vector<std::string> extracted;
  std::stringstream file , ss_line;
  std::string line , info;
  int counter_line = 1;

  file.str(file_context);
  file.clear();

  while(getline(file , line)){
    ss_line.str(line);
    ss_line.clear();
    if(counter_line > NUM_ROWS_HEADER){
      while(getline(ss_line , info , ',')){
        extracted.push_back(info);
      }
    }
    counter_line++;
  }
  return extracted;
}

std::vector<std::string> first_line_extractor_file(std::string file_context){
  std::vector<std::string> extracted;
  std::stringstream file , ss_line;
  std::string line , info;
  int counter_line = 1;

  file.str(file_context);
  file.clear();

  while(getline(file , line)){
    ss_line.str(line);
    ss_line.clear();
    if(counter_line == NUM_ROWS_HEADER){
      while(getline(ss_line , info , ',')){
        extracted.push_back(info);
      }
    }
    counter_line++;
  }
  return extracted;
}

bool contains_word(std::vector<std::string> input_vector , std::string word){
  for(int i = 0 ; i < input_vector.size() ; i++){
    if(input_vector[i] == word){
      return true;
    }
  }
  return false;
}

Response *Shop_html_interface::FirstPageHandler::callback(Request *req) {
  return Response::redirect("/admin");
}

Response *Shop_html_interface::AdminPageHandler::callback(Request *req){
  if(myshop->get_active_user_type() != "admin"){
    return Response::redirect("/401");
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body style=\"text-align: center;\">";
  body += "    <center> <a href=\"/logout\">Signout From Account</a> </center>";
  body += "    <h1>Admin Home</h1>";
  body += "    <h2>Upload Product Files</h2>";
  body += "    <div>";
  body += "      <form action=\"/admin\" method=\"post\" enctype=\"multipart/form-data\">";
  body += "        <center> <p>";
  body += "          <input name=\"file_type\" type=\"text\" placeholder=\"File Type\" />";
  body += "          <input name=\"file\" type=\"file\" />";
  body += "        </center> </p>";
  body += "        <p> <button type=\"submit\" >Upload</button> </p>";
  body += "      </form>";
  body += "    </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);  
  return res;
}

Response *Shop_html_interface::AdminHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "admin"){
    return Response::redirect("/401");
  }
  std::vector<std::string> all_file_words = extractor_file(req->getBodyParam("file"));
  std::vector<std::string> first_line_words = first_line_extractor_file(req->getBodyParam("file"));

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body style=\"text-align: center;\">";
  body += "    <center> <a href=\"/logout\">Signout From Account</a> </center>";
  body += "    <h1>Admin Home</h1>";
  body += "    <h2>Upload Product Files</h2>";
  body += "    <div>";
  body += "      <form action=\"/admin\" method=\"post\" enctype=\"multipart/form-data\">";
  body += "        <center> <p>";
  body += "          <input name=\"file_type\" type=\"text\" placeholder=\"File Type\" />";
  body += "          <input name=\"file\" type=\"file\" />";
  body += "        </center> </p>";
  body += "        <p> <button type=\"submit\" >Upload</button> </p>";
  body += "        <center><p style=\"color:green;\">___SUCCESS MESSAGE___</p></center>";
  body += "        <center><p>Importing Products Was Successful!!!</p></center>";
  body += "      </form>";
  body += "    </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);

  if(contains_word(first_line_words , "Num. of Seats") && req->getBodyParam("file_type") == "car"){
    myshop->import_product_html(all_file_words , req->getBodyParam("file_type"));
    return res;
  }else if(contains_word(first_line_words , "CPU Frequency") && req->getBodyParam("file_type") == "mobile"){
    myshop->import_product_html(all_file_words , req->getBodyParam("file_type"));
    return res;
  }else if(contains_word(first_line_words , "3D") && req->getBodyParam("file_type") == "tv"){
    myshop->import_product_html(all_file_words , req->getBodyParam("file_type"));
    return res;
  }
  body = "";
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body style=\"text-align: center;\">";
  body += "    <center> <a href=\"/logout\">Signout From Account</a> </center>";
  body += "    <h1>Admin Home</h1>";
  body += "    <h2>Upload Product Files</h2>";
  body += "    <div>";
  body += "      <form action=\"/admin\" method=\"post\" enctype=\"multipart/form-data\">";
  body += "        <center> <p>";
  body += "          <input name=\"file_type\" type=\"text\" placeholder=\"File Type\" />";
  body += "          <input name=\"file\" type=\"file\" />";
  body += "        </center> </p>";
  body += "        <p> <button type=\"submit\" >Upload</button> </p>";
  body += "        <center><p style=\"color:red;\">___MESSAGE___</p></center>";
  body += "        <center><p>Something Went Wrong Try Again!!!</p></center>";
  body += "      </form>";
  body += "    </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);
  return res;  
}

Response *Shop_html_interface::SignupHandler::callback(Request *req) {
  if(myshop->get_active_user_type() == "admin" || myshop->get_active_user_type() == "buyer" || myshop->get_active_user_type() == "seller"){
    return Response::redirect("/401");
  }
  std::vector<std::string> info;
  info.push_back("email");
  info.push_back(req->getBodyParam("email"));
  info.push_back("username");
  info.push_back(req->getBodyParam("username"));
  info.push_back("password");
  info.push_back(req->getBodyParam("password"));
  info.push_back("type");
  info.push_back(req->getBodyParam("userType"));

  if(req->getBodyParam("password") != req->getBodyParam("confirmPassword")){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "  <body>";
    body += "   <center> <p>Already a Member? Login to Your Account!</p> </center>";
    body += "   <center> <a href=\"/login\">Login Here!</a> </center>";
    body += "   <center> <h1>Shop AP</h1> </center>";
    body += "   <center> <h2>Sign up Today!</h2> </center>";
    body += "   <div>";
    body += "   <center>";
    body += "      <form action=\"/signup\" method=\"post\">";
    body += "        <p> <input name=\"email\" type=\"text\" placeholder=\"Email\" /> </p>";
    body += "        <p> <input name=\"username\" type=\"text\" placeholder=\"Username\" /> </p>";
    body += "        <p> <input name=\"password\" type=\"password\" placeholder=\"Password\" /> </p>";
    body += "        <p> <input name=\"confirmPassword\" type=\"password\" placeholder=\"Confirm Password\" /> </p>";
    body += "        <p>";
    body += "          <select name=\"userType\">";
    body += "            <option value=\"seller\">Seller</option>";
    body += "            <option value=\"buyer\">Buyer</option>";
    body += "          </select>";
    body += "        </p>";
    body += "        <p>";
    body += "          <button type=\"submit\" >Signup</button>";
    body += "        </p>";
    body += "        <p style=\"color:red;\">___MESSAGE___</p>";
    body += "        <p>Your Password and Confirm Password were different!!!</p>";
    body += "      </form>";
    body += "   </center>";
    body += "   </div>";
    body += "  </body>";
    body += "</html>";
    res->setBody(body);  
    return res;    
  }

  try{
    myshop->signup(info);
  }catch(signup_error e){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    std::string error_message(e.what());
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "  <body>";
    body += "    <center> <h1>Shop AP</h1> </center>";
    body += "    <center> <h2>Sign up Today!</h2> </center>";
    body += "    <div>";
    body += "    <center>";
    body += "      <form action=\"/signup\" method=\"post\">";
    body += "        <p> <input name=\"email\" type=\"text\" placeholder=\"Email\" /> </p>";
    body += "        <p> <input name=\"username\" type=\"text\" placeholder=\"Username\" /> </p>";
    body += "        <p> <input name=\"password\" type=\"password\" placeholder=\"Password\" /> </p>";
    body += "        <p> <input name=\"confirmPassword\" type=\"password\" placeholder=\"Confirm Password\" /> </p>";
    body += "        <p>";
    body += "            <select name=\"userType\">";
    body += "              <option value=\"seller\">Seller</option>";
    body += "              <option value=\"buyer\">Buyer</option>";
    body += "            </select>";
    body += "        </p>";
    body += "        <p>";
    body += "          <button type=\"submit\" >Signup</button>";
    body += "        </p>";
    body += "        <p style=\"color:red;\">___MESSAGE___</p>";
    body += "        <p>There was a problem in the sign up!!!</p>";
    body += "        <p>" + error_message + "</p>";
    body += "      </form>";
    body += "    </center>";
    body += "    </div>";
    body += "  </body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
  if(req->getBodyParam("userType") == "buyer"){
    Response *res = new Response;
    res = Response::redirect("/buyer?user_id=" + std::to_string(myshop->find_user_id_html(req->getBodyParam("email"))) );
    return res;
  }
  Response *res = new Response;
  res = Response::redirect("/seller?user_id=" + std::to_string(myshop->find_user_id_html(req->getBodyParam("email"))) );
  return res;
}

Response *Shop_html_interface::LoginHandler::callback(Request *req) {
  if(myshop->get_active_user_type() == "admin" || myshop->get_active_user_type() == "buyer" || myshop->get_active_user_type() == "seller"){
    return Response::redirect("/401");
  }
  std::vector<std::string> info;
  info.push_back("email");
  info.push_back(req->getBodyParam("email"));
  info.push_back("password");
  info.push_back(req->getBodyParam("password"));
  try{
    myshop->login(info);
  }catch(login_error e){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    std::string error_message(e.what());
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "  <body>";
    body += "    <center> <p>You don't have an account?</p> </center>";
    body += "    <center> <p>Sign up now!</p> </center>";
    body += "    <center> <a href=\"/signup\">Signup here!</a> </center>";
    body += "    <center> <h1>Shop AP</h1> </center>";
    body += "    <center> <h2>Login Here!</h2> </center>";
    body += "    <div>";
    body += "    <center>";
    body += "      <form action=\"/login\" method=\"post\">";
    body += "        <p> <input name=\"email\" type=\"text\" placeholder=\"Email\" /> </p>";
    body += "        <p> <input name=\"password\" type=\"password\" placeholder=\"Password\" /> </p>";
    body += "        <p> <button type=\"submit\" >Login</button> </p>";
    body += "        <p style=\"color:red;\">___MESSAGE___</p>";
    body += "        <p>There was a problem in the Log in!!!</p>";
    body += "        <p>" + error_message + "</p>";
    body += "      </form>";
    body += "    </center>";
    body += "    </div>";
    body += "  </body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
  if(myshop->find_user_type_html(req->getBodyParam("email")) == "buyer"){
    Response *res = new Response;
    res = Response::redirect("/buyer?user_id=" + std::to_string(myshop->find_user_id_html(req->getBodyParam("email"))) );
    return res;
  }else if(myshop->find_user_type_html(req->getBodyParam("email")) == "seller"){
    Response *res = new Response;
    res = Response::redirect("/seller?user_id=" + std::to_string(myshop->find_user_id_html(req->getBodyParam("email"))) );
    return res;
  }
  Response *res = new Response;
  res = Response::redirect("/admin");
  return res;
}

Response *Shop_html_interface::LogoutHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "admin" && myshop->get_active_user_type() != "buyer" && myshop->get_active_user_type() != "seller"){
    return Response::redirect("/401");
  }
  myshop->logout();
  return Response::redirect("/login");
}

Response *Shop_html_interface::OfferHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "seller"){
    return Response::redirect("/401");
  }
  std::vector<std::string> info;
  info.push_back("productId");
  info.push_back(req->getBodyParam("productId"));
  info.push_back("offerUnitPrice");
  info.push_back(req->getBodyParam("offerUnitPrice"));
  info.push_back("offerAmount");
  info.push_back(req->getBodyParam("offerAmount"));
  try{
    myshop->seller_offer(info);
  }catch(offer_error e){
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    std::string error_message(e.what());
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "  <body>";
    body += "    <center> <a href=\"/back_seller\">Return Home</a> </center>";
    body += "    <center> <h1>Shop AP</h1> </center>";
    body += "    <center> <h2>Create Seller Offer</h2> </center>";
    body += "    <div>";
    body += "    <center>";
    body += "      <form action=\"/offer\" method=\"post\">";
    body += "        <p> <input name=\"productId\" type=\"text\" placeholder=\"Product ID\" /> </p>";
    body += "        <p> <input name=\"offerUnitPrice\" type=\"text\" placeholder=\"Unit Price\" /> </p>";
    body += "        <p> <input name=\"offerAmount\" type=\"text\" placeholder=\"Amount\" /> </p>";
    body += "        <p> <button type=\"submit\" >Create Offer</button> </p>";
    body += "        <p style=\"color:red;\">___MESSAGE___</p>";
    body += "        <p>There was a problem in the Offer!!!</p>";
    body += "        <p>" + error_message + "</p>";
    body += "      </form>";
    body += "    </center>";
    body += "    </div>";
    body += "  </body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
  return Response::redirect("/offer");
}

Response *Shop_html_interface::OfferPageHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "seller"){
    return Response::redirect("/401");
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body>";
  body += "    <center> <a href=\"/back_seller\">Return Home</a> </center>";
  body += "    <center> <h1>Shop AP</h1> </center>";
  body += "    <center> <h2>Create Seller Offer</h2> </center>";
  body += "    <div>";
  body += "    <center>";
  body += "      <form action=\"/offer\" method=\"post\">";
  body += "        <p> <input name=\"productId\" type=\"text\" placeholder=\"Product ID\" /> </p>";
  body += "        <p> <input name=\"offerUnitPrice\" type=\"text\" placeholder=\"Unit Price\" /> </p>";
  body += "        <p> <input name=\"offerAmount\" type=\"text\" placeholder=\"Amount\" /> </p>";
  body += "        <p> <button type=\"submit\" >Create Offer</button> </p>";
  body += "        <center><p>____________________________</p></center>";
  body += "        <center><p>All Products</p></center>";
  body += "        <center><p>productId | productName</p></center>";
  body += "        <center><p>" + myshop->get_all_product_html() + "</p></center>";
  body += "      </form>";
  body += "    </center>";
  body += "    </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *Shop_html_interface::HelpSellerHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "seller"){
    return Response::redirect("/401");
  }
  return Response::redirect("/seller?user_id=" + std::to_string(myshop->get_active_user_id()));
}

Response *Shop_html_interface::SellerHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "seller"){
    return Response::redirect("/401");
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body style=\"text-align: center;\">";
  body += "    <center> <a href=\"/logout\">Signout From Account</a> </center>";
  body += "    <h1>Seller Home</h1>";
  body += "    <div>";
  body += "      <form action=\"/back_seller\" method=\"post\">";
  body += "        <center><p>Hello Seller!</p></center>";
  body += "        <center> <a href=\"/offer\">Create New Offer</a> </center>";
  body += "        <center><p>Your Offers:</p></center>";
  body += "        <center><p>productId | offerId | offerUnitPrice | offerAmount</p></center>";
  body += "        <center><p>" + myshop->get_seller_offers_string() + "</p></center>";
  body += "      </form>";
  body += "    </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *Shop_html_interface::BuyerPageHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "buyer"){
    return Response::redirect("/401");
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body style=\"text-align: center;\">";
  body += "    <center> <a href=\"/logout\">Signout From Account</a> </center>";
  body += "    <center> <a href=\"/cart?user_id=" + req->getQueryParam("user_id") + "\">Go to your cart</a> </center>";
  body += "    <center> <a href=\"/wallet?user_id=" + req->getQueryParam("user_id") + "\">Go to your Wallet</a> </center>";
  body += "    <h1>Buyer Home</h1>";
  body += "    <div>";
  body += "      <form action=\"/buyer\" method=\"post\">";
  body += "        <center><p>Hello Buyer!</p></center>";
  body += "        <center><p>____________________________</p></center>";
  body += "        <center><p>Shop Products</p></center>";
  body += "        <center><p>productId | productName</p></center>";
  for(int i = 0 ; i < myshop->get_all_products_vector_html().size() ; i++){
    body += "<center> <a href=\"/product?productId=" + 
            std::to_string(myshop->get_all_products_vector_html()[i]->get_product_id()) + 
            "\"> " +
            std::to_string(myshop->get_all_products_vector_html()[i]->get_product_id()) + 
            " | " 
            + myshop->get_all_products_vector_html()[i]->get_product_name() + "</a> </center>";
  }
  body += "      </form>";
  body += "    </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *Shop_html_interface::WalletPageHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "buyer"){
    return Response::redirect("/401");
  }
  std::vector<std::string> info;
  info.push_back("count");
  info.push_back("1");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body>";
  body += "    <center> <a href=\"/buyer?user_id=" + req->getQueryParam("user_id") + "\">Return Home</a> </center>";
  body += "    <center> <h1>Wallet</h1> </center>";
  body += "    <center> <h2>Buyer Transactions</h2> </center>";
  body += "    <div>";
  body += "    <center>";
  body += "      <form action=\"/wallet\" method=\"post\">";
  body += "        <p> Current Balance </p>";
  body += "        <p>" + myshop->get_wallet_html(info) + "</p>";
  body += "        <p> <input name=\"depositValue\" type=\"text\" placeholder=\"Deposit Amount\" /> </p>";
  body += "        <p> <button type=\"submit\" >Deposit</button> </p>";
  body += "      </form>";
  body += "    </center>";
  body += "    </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *Shop_html_interface::WalletHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "buyer"){
    return Response::redirect("/401");
  }
  std::vector<std::string> info , info_wallet;
  info.push_back("count");
  info.push_back("1");

  info_wallet.push_back("amount");
  info_wallet.push_back(req->getBodyParam("depositValue"));

  myshop->charge_buyer_wallet(info_wallet);
  return Response::redirect("/wallet?user_id=" + std::to_string(myshop->get_active_user_id()));
}

Response *Shop_html_interface::ProductPageHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "buyer"){
    return Response::redirect("/401");
  }
  std::vector<std::string> info;
  info.push_back("productId");
  info.push_back(req->getQueryParam("productId"));

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += "<style>";
  body += "table, th, td {";
  body += "  border: 1px solid black;";
  body += "  padding: 5px;";
  body += "}";
  body += "table {";
  body += "  border-spacing: 15px;";
  body += "}";
  body += "</style>";
  body += "</head>";
  body += "<body>";
  body += "<center> <a href=\"/buyer?user_id=" + std::to_string(myshop->get_active_user_id()) + "\">Return Home</a> </center>";
  body += "<center><h2>Product Page</h2></center>";
  body += "<center>";
  body += "<table style=\"width:35%\">";
  body += "<caption>Product Information</caption>";
  body += "  <tr>";
  body += "    <th>Feature</th>";
  body += "    <th>Value</th>";
  body += "  </tr>";
  body += myshop->get_all_products_vector_html()[std::stoi(req->getQueryParam("productId")) - 1]->get_product_info_html();
  body += "</table>";
  body += "<p style=\"color:red;\">____________________________________________________</p>";
  body += "<table style=\"width:35%\">";
  body += "<caption>Offers On Product</caption>";
  body += "  <tr>";
  body += "    <th>Offer ID</th>";
  body += "    <th>offer Unit Price</th>";
  body += "    <th>offer Amount</th>";
  body += "    <th>User Demand</th>";
  body += "    <th>Submit</th>";
  body += "  </tr>";
  body += myshop->offers_on_product_html(info);
  body += "</table>";
  body += "</center>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *Shop_html_interface::ProductHelpHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "buyer"){
    return Response::redirect("/401");
  }
  std::vector<std::string> info , info_product;
  info.push_back("offerId");
  info.push_back(req->getQueryParam("offerId"));
  info.push_back("amount");
  info.push_back(req->getBodyParam("userDemandAmount"));

  info_product.push_back("productId");
  info_product.push_back(req->getQueryParam("productId"));
  try{
    myshop->add_to_cart(info);
  }catch(offer_error e){
    std::string error_message(e.what());
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += "table, th, td {";
    body += "  border: 1px solid black;";
    body += "  padding: 5px;";
    body += "}";
    body += "table {";
    body += "  border-spacing: 15px;";
    body += "}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<center> <a href=\"/buyer?user_id=" + std::to_string(myshop->get_active_user_id()) + "\">Return Home</a> </center>";
    body += "<center><h2>Product Page</h2></center>";
    body += "<center>";
    body += "<table style=\"width:35%\">";
    body += "<caption>Product Information</caption>";
    body += "  <tr>";
    body += "    <th>Feature</th>";
    body += "    <th>Value</th>";
    body += "  </tr>";
    body += myshop->get_all_products_vector_html()[std::stoi(req->getQueryParam("productId")) - 1]->get_product_info_html();
    body += "</table>";
    body += "<p style=\"color:red;\">____________________________________________________</p>";
    body += "<table style=\"width:35%\">";
    body += "<caption>Offers On Product</caption>";
    body += "  <tr>";
    body += "    <th>Offer ID</th>";
    body += "    <th>offer Unit Price</th>";
    body += "    <th>offer Amount</th>";
    body += "    <th>User Demand</th>";
    body += "    <th>Submit</th>";
    body += "  </tr>";
    body += myshop->offers_on_product_html(info_product);
    body += "</table>";
    body += "<center><p style=\"color:red;\">___MESSAGE___</p></center>";
    body += "<center><p>Product amount demanded is higer than offer amount!!!</p></center>";
    body += "<center><p>" + error_message + "</p></center>";
    body += "</center>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
  return Response::redirect("/product?productId=" + req->getQueryParam("productId"));
}

Response *Shop_html_interface::CartPageHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "buyer"){
    return Response::redirect("/401");
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<head>";
  body += "<style>";
  body += "table, th, td {";
  body += "  border: 1px solid black;";
  body += "  padding: 5px;";
  body += "}";
  body += "table {";
  body += "  border-spacing: 15px;";
  body += "}";
  body += "</style>";
  body += "</head>";
  body += "<body>";
  body += "<center> <a href=\"/buyer?user_id=" + std::to_string(myshop->get_active_user_id()) + "\">Return Home</a> </center>";
  body += "<center><h2>Cart Page</h2></center>";
  body += "<center>";
  body += "<table style=\"width:35%\">";
  body += "<caption>Product Information</caption>";
  body += "  <tr>";
  body += "    <th>productId</th>";
  body += "    <th>productName</th>";
  body += "    <th>offerId</th>";
  body += "    <th>sellerId</th>";
  body += "    <th>totalPrice</th>";
  body += "    <th>amount</th>";
  body += "  </tr>";
  body += myshop->show_buyer_cart_html();
  body += "</center>";
  body += "<center>";
  body += "<p style=\"color:red;\">____________________________________________________</p>";
  body += "<center><p>Total Price: " + myshop->get_buyer_total_price() + "</p></center>";
  body += "</center>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response *Shop_html_interface::PurchaseHandler::callback(Request *req) {
  if(myshop->get_active_user_type() != "buyer"){
    return Response::redirect("/401");
  }
  try{
    myshop->submit_cart();
  }catch(credit_error e){
    std::string error_message(e.what());
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<style>";
    body += "table, th, td {";
    body += "  border: 1px solid black;";
    body += "  padding: 5px;";
    body += "}";
    body += "table {";
    body += "  border-spacing: 15px;";
    body += "}";
    body += "</style>";
    body += "</head>";
    body += "<body>";
    body += "<center> <a href=\"/buyer?user_id=" + std::to_string(myshop->get_active_user_id()) + "\">Return Home</a> </center>";
    body += "<center><h2>Cart Page</h2></center>";
    body += "<center>";
    body += "<table style=\"width:35%\">";
    body += "<caption>Product Information</caption>";
    body += "  <tr>";
    body += "    <th>productId</th>";
    body += "    <th>productName</th>";
    body += "    <th>offerId</th>";
    body += "    <th>sellerId</th>";
    body += "    <th>totalPrice</th>";
    body += "    <th>amount</th>";
    body += "  </tr>";
    body += myshop->show_buyer_cart_html();
    body += "</center>";
    body += "<center>";
    body += "<p style=\"color:red;\">____________________________________________________</p>";
    body += "<center><p>Total Price: " + myshop->get_buyer_total_price() + "</p></center>";
    body += "<p>A Problem Occured When Submitting Your Cart!!!</p>";
    body += "<p>" + error_message + "</p>";
    body += "</center>";
    body += "</body>";
    body += "</html>";
    res->setBody(body);
    return res;
  }
  return Response::redirect("/cart?user_id=" + std::to_string(myshop->get_active_user_id()));
}

Response *Shop_html_interface::LoginPageHandler::callback(Request *req){
  if(myshop->get_active_user_type() == "admin" || myshop->get_active_user_type() == "buyer" || myshop->get_active_user_type() == "seller"){
    return Response::redirect("/401");
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body>";
  body += "   <center> <p>You don't have an account?</p> </center>";
  body += "   <center> <p>Sign up now!</p> </center>";
  body += "   <center> <a href=\"/signup\">Signup here!</a> </center>";
  body += "   <center> <h1>Shop AP</h1> </center>";
  body += "   <center> <h2>Login Here!</h2> </center>";
  body += "   <div>";
  body += "   <center>";
  body += "      <form action=\"/login\" method=\"post\">";
  body += "        <p> <input name=\"email\" type=\"text\" placeholder=\"Email\" /> </p>";
  body += "        <p> <input name=\"password\" type=\"password\" placeholder=\"Password\" /> </p>";
  body += "        <p> <button type=\"submit\" >Login</button> </p>";
  body += "      </form>";
  body += "   </center>";
  body += "   </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);  
  return res;
}

Response *Shop_html_interface::SignupPageHandler::callback(Request *req){
  if(myshop->get_active_user_type() == "admin" || myshop->get_active_user_type() == "buyer" || myshop->get_active_user_type() == "seller"){
    return Response::redirect("/401");
  }
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "  <body>";
  body += "   <center> <p>Already a Member? Login to Your Account!</p> </center>";
  body += "   <center> <a href=\"/login\">Login Here!</a> </center>";
  body += "   <center> <h1>Shop AP</h1> </center>";
  body += "   <center> <h2>Sign up Today!</h2> </center>";
  body += "   <div>";
  body += "   <center>";
  body += "      <form action=\"/signup\" method=\"post\">";
  body += "        <p> <input name=\"email\" type=\"text\" placeholder=\"Email\" /> </p>";
  body += "        <p> <input name=\"username\" type=\"text\" placeholder=\"Username\" /> </p>";
  body += "        <p> <input name=\"password\" type=\"password\" placeholder=\"Password\" /> </p>";
  body += "        <p> <input name=\"confirmPassword\" type=\"password\" placeholder=\"Confirm Password\" /> </p>";
  body += "        <p>";
  body += "          <select name=\"userType\">";
  body += "            <option value=\"seller\">Seller</option>";
  body += "            <option value=\"buyer\">Buyer</option>";
  body += "          </select>";
  body += "        </p>";
  body += "        <p>";
  body += "          <button type=\"submit\" >Signup</button>";
  body += "        </p>";
  body += "      </form>";
  body += "   </center>";
  body += "   </div>";
  body += "  </body>";
  body += "</html>";
  res->setBody(body);  
  return res;
}