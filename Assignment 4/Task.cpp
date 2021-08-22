#include <string>

#include "Task.hpp"

Task::Task(std::string c_name , unsigned int c_estimatedTime , unsigned int c_priority , std::string c_description){
	name = c_name;
	estimatedTime = c_estimatedTime;
	priority = c_priority;
	description = c_description;
}

void Task::set_list(std::string c_list){
	current_list_name = c_list;
}

void Task::set_assigned(bool status){
	is_assigned = status;
}

void Task::complete_task(bool status){
	is_completed = status;
}

void Task::edit_task(unsigned int new_estimatedTime, unsigned int new_priority, std::string new_description){
	estimatedTime = new_estimatedTime;
	priority = new_priority;
	description = new_description;
}