#include <iostream>
#include <sstream>
#include <vector>
#include "Shop.hpp"

using namespace std;

#define SPACER "?"
#define SIGNUP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define IMPORT_PRODUCTS "importProducts"
#define OFFERS "offers"
#define GET_PRODUCTS "getProducts"
#define OFFER "offer"
#define MY_OFFERS "myOffers"
#define CHANGE_OFFER "changeOffer"
#define WALLET "wallet"
#define GENERATE_DISCOUNT_CODE "generateDiscountCode"
#define OFFERS_ON_PRODUCT "offersOnProduct"
#define PRODUCT_DETAIL "productDetail"
#define COMMENTS "comments"
#define ADD_TO_CART "addToCart"
#define CART "cart"
#define SUBMIT_CART "submitCart"
#define ORDERS "orders"
#define CHARGE_WALLET "chargeWallet"
#define COMMENT "comment"
#define COMPARE "compare"
#define GET "GET"
#define POST "POST"
#define EMAIL "email"
#define USERNAME "username"
#define PASSWORD "password"
#define TYPE "type"
#define FILE_PATH "filePath"
#define OFFER_ID "offerId"
#define PRODUCT_ID "productId"
#define OFFER_AMOUNT "offerAmount"
#define OFFER_UNIT_PRICE "offerUnitPrice"
#define EVALUATE_MODEL "evaluateModel"

std::vector<std::string> get_valid_commands(){
	std::vector<std::string> all_valid_commands;
	all_valid_commands.push_back(SIGNUP);
	all_valid_commands.push_back(LOGIN);
	all_valid_commands.push_back(LOGOUT);
	all_valid_commands.push_back(IMPORT_PRODUCTS);
	all_valid_commands.push_back(OFFERS);
	all_valid_commands.push_back(GET_PRODUCTS);
	all_valid_commands.push_back(OFFER);
	all_valid_commands.push_back(MY_OFFERS);
	all_valid_commands.push_back(CHANGE_OFFER);
	all_valid_commands.push_back(WALLET);
	all_valid_commands.push_back(GENERATE_DISCOUNT_CODE);
	all_valid_commands.push_back(OFFERS_ON_PRODUCT);
	all_valid_commands.push_back(PRODUCT_DETAIL);
	all_valid_commands.push_back(COMMENTS);
	all_valid_commands.push_back(ADD_TO_CART);
	all_valid_commands.push_back(CART);
	all_valid_commands.push_back(SUBMIT_CART);
	all_valid_commands.push_back(ORDERS);
	all_valid_commands.push_back(CHARGE_WALLET);
	all_valid_commands.push_back(COMMENT);
	all_valid_commands.push_back(COMPARE);
	all_valid_commands.push_back(EVALUATE_MODEL);
	return all_valid_commands;
}

bool is_command_found(std::string command){
	std::vector<std::string> all_valid_commands = get_valid_commands();
	for(int i = 0 ; i < all_valid_commands.size() ; i++){
		if(all_valid_commands[i] == command){
			return true;
		}
	}
	return false;
}

int main()
{
	Shop myshop;

	string command_sentence;
	stringstream ss_command_sentence;

	string word;

	std::vector<string> command_words;

	while(getline(cin , command_sentence)){
		ss_command_sentence.str(command_sentence);
		ss_command_sentence.clear();
		while(getline(ss_command_sentence , word , ' ')){
			command_words.push_back(word);
		}

		try{
			if(command_words[0] != POST && command_words[0] != GET){
				throw bad_command_error();
			}
		}catch(bad_command_error e){
			std::cerr << e.what();
			command_words.clear();
			continue;
		}

		try{
			if(!is_command_found(command_words[1])){
				throw command_not_found_error();
			}
		}catch(command_not_found_error e){
			std::cerr << e.what();
			command_words.clear();
			continue;
		}

		try{
			if(command_words[0] == POST){
				if(command_words[1] == SIGNUP){
					if(command_words[2] == SPACER && command_words[3] == EMAIL && command_words[5] == USERNAME && command_words[7] == PASSWORD && command_words.size() == 9){
						myshop.signup(command_words);
					}else if(command_words[2] == SPACER && command_words[3] == EMAIL && command_words[5] == USERNAME && command_words[7] == PASSWORD && command_words.size() == 11){
						if(command_words[9] == TYPE){
							myshop.signup(command_words);
						}else{
							throw bad_command_error();
						}
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == LOGIN){
					if(command_words.size() != 7){
						throw bad_command_error();
					}
					if(command_words[2] == SPACER && command_words[3] == EMAIL && command_words[5] == PASSWORD){
						myshop.login(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == IMPORT_PRODUCTS){
					if(command_words.size() != 7){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == TYPE && command_words[5] == FILE_PATH){
						myshop.import_product(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == LOGOUT){
					if(command_words.size() != 2){
						throw bad_command_error();
					}
					myshop.logout();
				}else if(command_words[1] == OFFER){
					if(command_words.size() != 9){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == PRODUCT_ID && command_words[5] == OFFER_UNIT_PRICE && command_words[7] == OFFER_AMOUNT){
						myshop.seller_offer(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == CHANGE_OFFER){
					if(command_words.size() != 9){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == OFFER_ID && command_words[5] == OFFER_UNIT_PRICE && command_words[7] == OFFER_AMOUNT){
						myshop.change_offer(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == COMMENT){		
					if(command_words[2] == SPACER && command_words[3] == PRODUCT_ID && command_words[5] == COMMENT){
						myshop.post_comment(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == GENERATE_DISCOUNT_CODE){
					if(command_words.size() != 9){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == OFFER_ID && command_words[5] == "discountPercent" && command_words[7] == "discountNumber"){
						myshop.generate_discount_code(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == ADD_TO_CART){
					if(command_words[2] == SPACER && command_words[3] == OFFER_ID && command_words[5] == "amount" && command_words.size() == 7){
						myshop.add_to_cart(command_words);
					}else if(command_words[2] == SPACER && command_words[3] == OFFER_ID && command_words[5] == "amount" && command_words.size() == 9){
						if(command_words[7] == "discountCode"){
							myshop.add_to_cart(command_words);
						}else{
							throw bad_command_error();
						}
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == CHARGE_WALLET){
					if(command_words.size() != 5){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == "amount"){
						myshop.charge_buyer_wallet(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == SUBMIT_CART){
					if(command_words.size() != 2){
						throw bad_command_error();
					}
					myshop.submit_cart();
				}else if(command_words[1] == EVALUATE_MODEL){
					if(command_words.size() != 2){
						throw bad_command_error();
					}
					myshop.evaluate_model();					
				}

			}else if(command_words[0] == GET){
				if(command_words[1] == GET_PRODUCTS){
					if(command_words.size() != 2){
						throw bad_command_error();
					}
					myshop.get_products();
				}else if(command_words[1] == MY_OFFERS){
					if(command_words.size() != 2){
						throw bad_command_error();
					}
					myshop.get_seller_offers();
				}else if(command_words[1] == OFFERS_ON_PRODUCT){
					if(command_words.size() != 5){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == PRODUCT_ID){
						myshop.offers_on_product(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == PRODUCT_DETAIL){
					if(command_words.size() != 5){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == PRODUCT_ID){
						myshop.product_detail(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == COMMENTS){
					if(command_words.size() != 5){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == PRODUCT_ID){
						myshop.get_product_comments(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == CART){
					if(command_words.size() != 2){
						throw bad_command_error();
					}
					myshop.show_buyer_cart();
				}else if(command_words[1] == WALLET){
					if(command_words.size() != 5){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == "count"){
						myshop.get_wallet(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == ORDERS){
					if(command_words.size() != 5){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == "count"){
						myshop.get_buyer_orders(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == COMPARE){
					if(command_words.size() != 7){
						throw bad_command_error();
					}				
					if(command_words[2] == SPACER && command_words[3] == "productId1" && command_words[5] == "productId2"){
						myshop.compare_products(command_words);
					}else{
						throw bad_command_error();
					}
				}else if(command_words[1] == OFFERS){
					if(command_words.size() != 7 && command_words.size() != 2){
						throw bad_command_error();
					}
					if(command_words[2] == SPACER && command_words[3] == "order" && command_words[5] == "field"){
						myshop.show_admin_offers(command_words);
					}else if(command_words.size() == 2){
						myshop.show_buyer_all_offers();
					}else{
						throw bad_command_error();
					}
				}
			}
		}catch(bad_command_error e){
				std::cerr << e.what();
				command_words.clear();
				continue;
		}
		command_words.clear();
	}
	return 0;
}
