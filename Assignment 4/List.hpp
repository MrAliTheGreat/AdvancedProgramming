#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "Task.hpp"
#include <vector>
#include <string>

class List
{
public:
	List(std::string c_name);

	std::string get_name(){ return name; };
	std::vector<Task> get_list_tasks(){ return list_tasks; };

	std::string add_task_to_list(Task new_task);
	std::string delete_task(std::string task_name);
	void change_task(std::string old_task_name , Task new_task);

private:
	std::string name;
	std::vector<Task> list_tasks;
};

#endif