#ifndef __USER_HPP__
#define __USER_HPP__

#include "Task.hpp"
#include <vector>
#include <string>

class User
{
public:
	User(std::string c_name);

	std::string get_name(){ return name; };
	std::vector<Task> get_tasks() { return user_tasks; };

	void assign_task(Task& new_task);
	void change_task(std::string old_task_name , Task new_task);
	int time_all_tasks();
	int time_incompleted_tasks();
	int time_completed_tasks();
private:
	std::string name;
	std::vector<Task> user_tasks;
};

#endif