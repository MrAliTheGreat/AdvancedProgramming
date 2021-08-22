class signup_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Bad Request\n";
	}
};

class login_error : public std::exception
{
public:
	virtual const char* what() const throw(){
		return "Bad Request\n";
	}
};