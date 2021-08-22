#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <string>

class Task
{
public:
	Task(std::string c_name , unsigned int c_estimatedTime , unsigned int c_priority , std::string c_description);

	std::string get_name(){ return name; };
	unsigned int get_estimatedTime(){ return estimatedTime; };
	unsigned int get_priority(){ return priority; };
	std::string get_description(){ return description; };
	std::string get_list(){ return current_list_name; };
	bool get_is_completed(){ return is_completed; };
	bool get_is_assigned(){ return is_assigned; };

	void set_list(std::string c_list);
	void set_assigned(bool status);
	void complete_task(bool status);
	void edit_task(unsigned int estimatedTime, unsigned int priority, std::string description);

private:
	std::string name;
	unsigned int estimatedTime;
	unsigned int priority;
	std::string description;
	std::string current_list_name;
	bool is_completed = false;
	bool is_assigned = false;
};

#endif