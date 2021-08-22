#ifndef __COMMENT_H__
#define __COMMENT_H__

#include <string>

class Comment
{
public:
	Comment(std::string _comment_sentence , std::string _user_posted);
	std::string get_comment_sentence(){ return comment_sentence; };
	std::string get_user_posted(){ return user_posted; };
private:
	std::string comment_sentence;
	std::string user_posted;
};

#endif