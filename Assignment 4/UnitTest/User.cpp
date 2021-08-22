#include <vector>
#include <string>

#include "User.hpp"
#include "Task.hpp"

User::User(std::string c_name){
	name = c_name;
}

void User::assign_task(Task& new_task){
	new_task.set_assigned(true);
	user_tasks.push_back(new_task);
}

int User::time_all_tasks(){
	int sum_time = 0;
	for(int i = 0 ; i < user_tasks.size() ; i++){
		sum_time = sum_time + user_tasks[i].get_estimatedTime();
	}
	return sum_time;
}

int User::time_completed_tasks(){
	int sum_time = 0;
	for(int i = 0 ; i < user_tasks.size() ; i++){
		if(user_tasks[i].get_is_completed()){
			sum_time = sum_time + user_tasks[i].get_estimatedTime();
		}
	}
	return sum_time;
}

int User::time_incompleted_tasks(){
	int sum_time = 0;
	for(int i = 0 ; i < user_tasks.size() ; i++){
		if(!user_tasks[i].get_is_completed()){
			sum_time = sum_time + user_tasks[i].get_estimatedTime();
		}
	}
	return sum_time;
}

void User::change_task(std::string old_task_name , Task new_task){
	for(int i = 0 ; i < user_tasks.size() ; i++){
		if(user_tasks[i].get_name() == old_task_name){
			user_tasks[i] = new_task;
		}
	}
}