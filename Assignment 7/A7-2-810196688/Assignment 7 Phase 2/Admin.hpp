#ifndef __ADMIN_H__
#define __ADMIN_H__

#include "User.hpp"
#include "Offer.hpp"

#include <string>
#include <vector>

class Admin : public User
{
public:
	Admin();
	void show_offers(std::vector<User*> users , std::string sort_order , std::string field_offers);
private:
	std::vector<Offer*> all_offers;
};

#endif