#include <vector>
#include <string>

#include "List.hpp"
#include "Task.hpp"

List::List(std::string c_name){
	name = c_name;
}

bool already_existing_task(std::vector<Task> input_vector , Task input_object){
	for(int i = 0 ; i < input_vector.size() ; i++){
		if(input_vector[i].get_name() == input_object.get_name()){
			return true;
		}
	}
	return false;
}

std::string List::add_task_to_list(Task new_task){
	if(already_existing_task(list_tasks , new_task)){
		return "Task already exists";
	}
	list_tasks.push_back(new_task);
	return "Success";
}


std::string List::delete_task(std::string task_name){
	for(int i = 0 ; i < list_tasks.size() ; i++){
		if(list_tasks[i].get_name() == task_name){
			list_tasks.erase(list_tasks.begin() + i);
			return "Success";
		}
	}
	return "";
}

void List::change_task(std::string old_task_name , Task new_task){
	for(int i = 0 ; i < list_tasks.size() ; i++){
		if(list_tasks[i].get_name() == old_task_name){
			list_tasks[i] = new_task;
		}
	}
}