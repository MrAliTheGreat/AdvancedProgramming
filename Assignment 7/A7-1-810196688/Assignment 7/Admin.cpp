#include "Admin.hpp"

#include <string>
#include <algorithm>
#include <iostream>

#define ASCEND "ASCEND"
#define DESCEND "DESCEND"
#define OFFER_ID "offerId"
#define PRODUCT_ID "productId"
#define OFFER_AMOUNT "offerAmount"
#define OFFER_UNIT_PRICE "offerUnitPrice"
#define OFFER_TITLE "productId | offerId | offerUnitPrice | offerAmount\n"

Admin::Admin() : User(-2 , "admin" , "admin" , "admin@gmail.com" , "admin"){}

bool sort_product_Id_ascend(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_product_id() < offer_2->get_product_id()); }

bool sort_product_Id_descend(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_product_id() > offer_2->get_product_id()); }

bool sort_offer_Id_ascend(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_offer_id() < offer_2->get_offer_id()); }

bool sort_offer_Id_descend(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_offer_id() > offer_2->get_offer_id()); }

bool sort_unit_price_ascend(Offer* offer_1 , Offer* offer_2){ 
	if(offer_1->get_unit_price() == offer_2->get_unit_price()){
		return offer_1->get_offer_id() < offer_2->get_offer_id();
	}
	return (offer_1->get_unit_price() < offer_2->get_unit_price());
}

bool sort_unit_price_descend(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_unit_price() > offer_2->get_unit_price()); }

bool sort_quantity_ascend(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_quantity() < offer_2->get_quantity()); }

bool sort_quantity_descend(Offer* offer_1 , Offer* offer_2){ return (offer_1->get_quantity() > offer_2->get_quantity()); }

void Admin::show_offers(std::vector<User*> users , std::string sort_order , std::string field_offers){
	for(int i = 0 ; i < users.size() ; i++){
		for(int j = 0 ; j < users[i]->get_seller_offers().size() ; j++){
			all_offers.push_back(users[i]->get_seller_offers()[j]);
		}
	}
	if(field_offers == PRODUCT_ID && sort_order == ASCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_product_Id_ascend);
	}else if(field_offers == PRODUCT_ID && sort_order == DESCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_product_Id_descend);
	}else if(field_offers == OFFER_ID && sort_order == ASCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_offer_Id_ascend);
	}else if(field_offers == OFFER_ID && sort_order == DESCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_offer_Id_descend);
	}else if(field_offers == OFFER_UNIT_PRICE && sort_order == ASCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_unit_price_ascend);
	}else if(field_offers == OFFER_UNIT_PRICE && sort_order == DESCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_product_Id_descend);
	}else if(field_offers == OFFER_AMOUNT && sort_order == ASCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_quantity_ascend);
	}else if(field_offers == OFFER_AMOUNT && sort_order == DESCEND){
		std::sort(all_offers.begin() , all_offers.end() , sort_quantity_descend);
	}

	std::cout << OFFER_TITLE;
	for(int i = 0 ; i < all_offers.size() ; i++){
		std::cout << all_offers[i]->get_product_id() << " | ";
		std::cout << all_offers[i]->get_offer_id() << " | ";
		std::cout << all_offers[i]->get_unit_price() << " | ";
		std::cout << all_offers[i]->get_quantity() << "\n";
	}
	all_offers.clear();
}