#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <stdlib.h>
#include <exception>

#define PERMISSION_MESSAGE "Permission Denied\n"
#define NOT_FOUND_MESSAGE "Not Found\n"
#define REQUEST_MESSAGE "Bad Request\n"

class signup_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class login_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class logout_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return PERMISSION_MESSAGE;
	}
};

class access_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return PERMISSION_MESSAGE;
	}
};

class file_existance_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return NOT_FOUND_MESSAGE;
	}
};

class offer_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class discount_code_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class credit_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class no_order_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return NOT_FOUND_MESSAGE;
	}
};

class invalid_money_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class no_offer_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return NOT_FOUND_MESSAGE;
	}
};

class incomparable_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class no_product_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return NOT_FOUND_MESSAGE;
	}
};

class bad_command_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return REQUEST_MESSAGE;
	}
};

class command_not_found_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return NOT_FOUND_MESSAGE;
	}
};

#endif