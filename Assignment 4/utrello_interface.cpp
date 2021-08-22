#include <string>
#include <vector>
#include <algorithm>

#include "utrello_interface.hpp"
#include "User.hpp"
#include "List.hpp"
#include "Task.hpp"

UTrelloInterface::UTrelloInterface(){ }

bool already_existing_user(std::vector<User> input_vector , std::string input_name){
	for(int i = 0 ; i < input_vector.size() ; i++){	
		if(input_name == input_vector[i].get_name()){
			return true;
		}
	}
	return false;
}

bool already_existing_list(std::vector<List> input_vector , std::string input_name){
	for(int i = 0 ; i < input_vector.size() ; i++){	
		if(input_name == input_vector[i].get_name()){
			return true;
		}
	}
	return false;
}

bool already_existing_task(std::vector<Task> input_vector , std::string input_name){
	for(int i = 0 ; i < input_vector.size() ; i++){	
		if(input_name == input_vector[i].get_name()){
			return true;
		}
	}
	return false;
}

List list_finder(std::vector<List> list_vector , std::string list_name){
	for(int i = 0 ; i < list_vector.size() ; i++){
		if(list_vector[i].get_name() == list_name){
			return list_vector[i];
		}
	}
	return List("");
}

List list_with_task_finder(std::vector<List> list_vector , std::string task_name){
	for(int i = 0 ; i < list_vector.size() ; i++){
		for(int j = 0 ; j < list_vector[i].get_list_tasks().size() ; j++){
			if(list_vector[i].get_list_tasks()[j].get_name() == task_name){
				return list_vector[i];
			}
		}
	}
	return List("");
}

int list_with_task_index_finder(std::vector<List> list_vector , std::string task_name){
	for(int i = 0 ; i < list_vector.size() ; i++){
		for(int j = 0 ; j < list_vector[i].get_list_tasks().size() ; j++){
			if(list_vector[i].get_list_tasks()[j].get_name() == task_name){
				return i;
			}
		}
	}
	return -1;
}

int list_index_finder(std::vector<List> list_vector , std::string list_name){
	for(int i = 0 ; i < list_vector.size() ; i++){
		if(list_vector[i].get_name() == list_name){
			return i;
		}
	}
	return -1;
}

User user_finder(std::vector<User> user_vector , std::string user_name){
	for(int i = 0 ; i < user_vector.size() ; i++){
		if(user_vector[i].get_name() == user_name){
			return user_vector[i];
		}
	}
	return User("");
}

User user_with_task_finder(std::vector<User> user_vector , std::string task_name){
	for(int i = 0 ; i < user_vector.size() ; i++){
		for(int j = 0 ; j < user_vector[i].get_tasks().size() ; j++){
			if(user_vector[i].get_tasks()[j].get_name() == task_name){
				return user_vector[i];
			}
		}
	}
	return User("");
}

int user_with_task_index_finder(std::vector<User> user_vector , std::string task_name){
	for(int i = 0 ; i < user_vector.size() ; i++){
		for(int j = 0 ; j < user_vector[i].get_tasks().size() ; j++){
			if(user_vector[i].get_tasks()[j].get_name() == task_name){
				return i;
			}
		}
	}
	return -1;
}

int user_index_finder(std::vector<User> user_vector , std::string user_name){
	for(int i = 0 ; i < user_vector.size() ; i++){
		if(user_vector[i].get_name() == user_name){
			return i;
		}
	}
	return -1;
}

Task task_finder(std::vector<Task> task_vector , std::string task_name){
	for(int i = 0 ; i < task_vector.size() ; i++){
		if(task_vector[i].get_name() == task_name){
			return task_vector[i];
		}
	}
	return Task("" , 0 , 0 , "");
}

int task_index_finder(std::vector<Task> task_vector , std::string task_name){
	for(int i = 0 ; i < task_vector.size() ; i++){
		if(task_vector[i].get_name() == task_name){
			return i;
		}
	}
	return -1;
}

std::string UTrelloInterface::addUser(std::string username){
	User new_user(username);
	if(already_existing_user(all_users , username)){
		return "User‬‬ ‫‪already‬‬ ‫‪exists‬‬";
	}
	all_users.push_back(new_user);
	return "Success";
}

std::string UTrelloInterface::addList(std::string name){
	List new_list(name);
	if(already_existing_list(all_lists , name)){
		return "List ‫‪already‬‬ ‫‪exists‬‬";
	}
	all_lists.push_back(new_list);
	return "Success";
}

std::string UTrelloInterface::addTask(std::string list, std::string name, unsigned int estimatedTime, unsigned int priority, std::string description){
	Task new_task(name , estimatedTime , priority , description);
	if(already_existing_list(all_lists , list)){
		if(already_existing_task(all_tasks , name)){
			return "Task already exists";
		}

		new_task.set_list(list);
		all_tasks.push_back(new_task);
		List target_list = list_finder(all_lists , list);
		target_list.add_task_to_list(new_task);
		all_lists[list_index_finder(all_lists , list)] = target_list;
		return "Success";
	}
	return "List does not exist";
}

std::string UTrelloInterface::deleteList(std::string list){
	for(int i = 0 ; i < all_lists.size() ; i++){
		if(all_lists[i].get_name() == list){
			all_lists.erase(all_lists.begin() + i);
			return "Success";
		}
	}
	return "List does not exist";
}

std::string UTrelloInterface::deleteTask(std::string task){
	for(int i = 0 ; i < all_lists.size() ; i++){
		std::string result_delete = all_lists[i].delete_task(task);
		if(result_delete != ""){
			all_tasks.erase(all_tasks.begin() + task_index_finder(all_tasks , task));
			return result_delete;
		}
	}
	return "Task does not exist";
}

std::string UTrelloInterface::assignTask(std::string task, std::string user){
	if(already_existing_task(all_tasks , task)){
		if(already_existing_user(all_users , user)){
			User target_user = user_finder(all_users , user);
			Task target_task = task_finder(all_tasks , task);
			List target_list = list_with_task_finder(all_lists , task);

			target_user.assign_task(target_task);
			all_users[user_index_finder(all_users , user)] = target_user;
			all_tasks[task_index_finder(all_tasks , task)] = target_task;

			target_list.change_task(task , target_task);
			all_lists[list_with_task_index_finder(all_lists , task)] = target_list;
			return "Success";
		}
		return "User does not exist";
	}
	return "Task does not exist";
}

std::string UTrelloInterface::editTask(std::string task, unsigned int estimatedTime, unsigned int priority, std::string description){
	if(already_existing_task(all_tasks , task)){
		Task target_task = task_finder(all_tasks , task);
		target_task.edit_task(estimatedTime , priority , description);
		all_tasks[task_index_finder(all_tasks , task)] = target_task;
		return "Success";
	}
	return "Task does not exist";
}

std::string UTrelloInterface::moveTask(std::string task, std::string list){
	if(already_existing_list(all_lists , list)){
		if(already_existing_task(all_tasks , task)){
			List new_list = list_finder(all_lists , list);
			Task moving_task = task_finder(all_tasks , task);
			List old_list = list_finder(all_lists , moving_task.get_list());
			int task_index_old_list = list_index_finder(all_lists , moving_task.get_list());

			new_list.add_task_to_list(moving_task);
			all_lists[list_index_finder(all_lists , list)] = new_list;
			old_list.delete_task(task);	
			all_lists[task_index_old_list] = old_list;
			return "Success";
		}
		return "Task does not exist";
	}
	return "List does not exist";
}

std::string UTrelloInterface::completeTask(std::string task){
	if(already_existing_task(all_tasks , task)){
		Task target_task = task_finder(all_tasks , task);
		target_task.complete_task(true);
		all_tasks[task_index_finder(all_tasks , task)] = target_task;

		List target_list = list_finder(all_lists , target_task.get_list());
		target_list.change_task(task , target_task);
		all_lists[list_index_finder(all_lists , target_task.get_list())] = target_list;

		User target_user = user_with_task_finder(all_users , task);
		target_user.change_task(task , target_task);
		all_users[user_with_task_index_finder(all_users , task)] = target_user;
		return "Success";
	}
	return "Task does not exist";
}

int UTrelloInterface::printTotalEstimatedTime(){
	int total_estimated_time = 0;
	for(int i = 0 ; i < all_users.size() ; i++){
		int user_max_time = all_users[i].time_all_tasks();
		if(user_max_time > total_estimated_time){
			total_estimated_time = user_max_time;
		}
	}
	return total_estimated_time;
}

int UTrelloInterface::printTotalRemainingTime(){
	int total_estimated_time = 0;
	for(int i = 0 ; i < all_users.size() ; i++){
		int user_max_time = all_users[i].time_incompleted_tasks();
		if(user_max_time > total_estimated_time){
			total_estimated_time = user_max_time;
		}
	}
	return total_estimated_time;
}

int UTrelloInterface::printUserWorkload(std::string user){
	if(already_existing_user(all_users , user)){
		return user_finder(all_users , user).time_all_tasks();
	}
	return 0;
}

std::string UTrelloInterface::printTask(std::string task){
	if(already_existing_task(all_tasks , task)){
		Task target_task = task_finder(all_tasks , task);
		User target_user = user_with_task_finder(all_users , task);
		std::string return_message = target_task.get_name() + "\n" +
									 target_task.get_description() + "\n" +
									 "Priority: " + std::to_string(target_task.get_priority()) + "\n" +
									 "Estimated Time: " + std::to_string(target_task.get_estimatedTime()) + "\n";
		if(target_user.get_name() == ""){
			return return_message + "Unassigned\n";
		}
		return return_message + "Assigned to " + target_user.get_name() + "\n";
	}
	return "Task does not exist";
}

std::string UTrelloInterface::printList(std::string list){
	if(already_existing_list(all_lists , list)){
		std::vector<Task> list_tasks = list_finder(all_lists , list).get_list_tasks();
		std::string return_message = "List " + list + "\n";
		for(int i = 0 ; i < list_tasks.size() ; i++){
			return_message = return_message + std::to_string(list_tasks[i].get_priority()) + " | " +
											  list_tasks[i].get_name() + " | ";
			if(user_with_task_finder(all_users , list_tasks[i].get_name()).get_name() == ""){
				return_message = return_message + "Unassigned | ";
			}else{
				return_message = return_message + user_with_task_finder(all_users , list_tasks[i].get_name()).get_name() + " | ";
			}
			return_message = return_message + std::to_string(list_tasks[i].get_estimatedTime()) + "h\n";
		}
		return return_message;
	}
	return "List does not exist";
}

std::string UTrelloInterface::printAllLists(){
	std::string return_message = "";
	for(int i = 0 ; i < all_lists.size() ; i++){
		return_message = return_message + printList(all_lists[i].get_name()) + "\n";
	}
	return return_message;
}

std::string UTrelloInterface::printUserTasks(std::string user){
	if(already_existing_user(all_users , user)){
		std::vector<Task> user_tasks = user_finder(all_users , user).get_tasks();
		std::string return_message = "";
		for(int i = 0 ; i < user_tasks.size() ; i++){
			return_message = return_message + std::to_string(user_tasks[i].get_priority()) + " | " +
							 				  user_tasks[i].get_name() + " | " +
							 				  user + " | " +
							 				  std::to_string(user_tasks[i].get_estimatedTime()) + "h\n";
		}
		return return_message;
	}
	return "User does not exist";
}

std::string UTrelloInterface::printUserUnfinishedTasks(std::string user){
	if(already_existing_user(all_users , user)){
		std::vector<Task> user_tasks = user_finder(all_users , user).get_tasks();
		std::string return_message = "";
		for(int i = 0 ; i < user_tasks.size() ; i++){
			if(!user_tasks[i].get_is_completed()){
				return_message = return_message + std::to_string(user_tasks[i].get_priority()) + " | " +
								 				  user_tasks[i].get_name() + " | " +
								 				  user + " | " +
								 				  std::to_string(user_tasks[i].get_estimatedTime()) + "h\n";
			}
		}
		return return_message;
	}
	return "User does not exist";
}

std::vector<Task> generate_unassigned_tasks(std::vector<Task> all_tasks){
	std::vector<Task> usassigned_tasks;
	for(int i = 0 ; i < all_tasks.size() ; i++){
		if(!all_tasks[i].get_is_assigned()){
			usassigned_tasks.push_back(all_tasks[i]);
		}
	}
	return usassigned_tasks;
}

std::vector<int> generate_unassigned_tasks_priorities(std::vector<Task> unassigned_tasks){
	std::vector<int> usassigned_tasks_priorities;
	for(int i = 0 ; i < unassigned_tasks.size() ; i++){
		usassigned_tasks_priorities.push_back(unassigned_tasks[i].get_priority());
	}
	return usassigned_tasks_priorities;
}

Task task_finder_by_priority(std::vector<Task> tasks , int priority){
	for(int i = 0 ; i < tasks.size() ; i++){
		if(tasks[i].get_priority() == priority){
			return tasks[i];
		}
	}
	return Task("" , 0 , 0 , "");
}

int task_index_finder_by_priority(std::vector<Task> tasks , int priority){
	for(int i = 0 ; i < tasks.size() ; i++){
		if(tasks[i].get_priority() == priority){
			return i;
		}
	}
	return -1;
}

std::string UTrelloInterface::printUnassignedTasksByPriority(){
	std::vector<Task> usassigned_tasks = generate_unassigned_tasks(all_tasks);
	std::vector<int> usassigned_tasks_priorities = generate_unassigned_tasks_priorities(usassigned_tasks);
	std::sort(usassigned_tasks_priorities.begin() , usassigned_tasks_priorities.end());
	std::string return_message = "";
	for(int i = 0 ; i < usassigned_tasks_priorities.size() ; i++){
		Task target_task = task_finder_by_priority(usassigned_tasks , usassigned_tasks_priorities[i]);
		return_message = return_message + std::to_string(usassigned_tasks_priorities[i]) + " | " +
										  target_task.get_name() + " | " +
										  "‫‪Unassigned‬‬" + " | " +
										  std::to_string(target_task.get_estimatedTime()) + "h\n";
		usassigned_tasks.erase(usassigned_tasks.begin() + task_index_finder_by_priority(usassigned_tasks , usassigned_tasks_priorities[i]));
	}
	return return_message;
}

std::vector<Task> generate_incompleted_tasks(std::vector<Task> all_tasks){
	std::vector<Task> incompleted_tasks;
	for(int i = 0 ; i < all_tasks.size() ; i++){
		if(!all_tasks[i].get_is_completed()){
			incompleted_tasks.push_back(all_tasks[i]);
		}
	}
	return incompleted_tasks;
}

std::vector<int> generate_incompleted_tasks_priorities(std::vector<Task> incompleted_tasks){
	std::vector<int> incompleted_tasks_priorities;
	for(int i = 0 ; i < incompleted_tasks.size() ; i++){
		incompleted_tasks_priorities.push_back(incompleted_tasks[i].get_priority());
	}
	return incompleted_tasks_priorities;
}

std::string UTrelloInterface::printAllUnfinishedTasksByPriority(){
	std::vector<Task> incompleted_tasks = generate_incompleted_tasks(all_tasks);
	std::vector<int> incompleted_tasks_priorities = generate_incompleted_tasks_priorities(incompleted_tasks);
	std::sort(incompleted_tasks_priorities.begin() , incompleted_tasks_priorities.end());
	std::string return_message = "";
	for(int i = 0 ; i < incompleted_tasks_priorities.size() ; i++){
		Task target_task = task_finder_by_priority(incompleted_tasks , incompleted_tasks_priorities[i]);
		return_message = return_message + std::to_string(incompleted_tasks_priorities[i]) + " | " +
										  target_task.get_name() + " | ";
		if(already_existing_user(all_users , user_with_task_finder(all_users , target_task.get_name()).get_name())){
			return_message = return_message + user_with_task_finder(all_users , target_task.get_name()).get_name() + " | ";
		}else{
			return_message = return_message + "‫‪Unassigned‬‬" + " | ";
		}
		return_message = return_message + std::to_string(target_task.get_estimatedTime()) + "h\n";
		incompleted_tasks.erase(incompleted_tasks.begin() + task_index_finder_by_priority(incompleted_tasks , incompleted_tasks_priorities[i]));
	}
	return return_message;
}

User find_user_by_time(std::vector<User> all_users , int time){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i].time_all_tasks() == time){
			return all_users[i];
		}
	}
	return User("");
}

int find_user_index_by_time(std::vector<User> all_users , int time){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i].time_all_tasks() == time){
			return i;
		}
	}
	return -1;
}

std::string UTrelloInterface::printUsersByWorkload(){
	std::vector<int> all_times;
	std::vector<User> all_users_copy = all_users;
	std::string return_message = "";
	for(int i = 0 ; i < all_users_copy.size() ; i++){
		all_times.push_back(all_users_copy[i].time_all_tasks());
	}
	std::sort(all_times.begin() , all_times.end());
	for(int i = 0 ; i < all_times.size() ; i++){
		return_message = return_message + find_user_by_time(all_users_copy , all_times[i]).get_name() + "\n";
		all_users_copy.erase(all_users_copy.begin() + find_user_index_by_time(all_users_copy , all_times[i]));
	}
	return return_message;
}

User find_user_by_completedTime(std::vector<User> all_users , int time){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i].time_completed_tasks() == time){
			return all_users[i];
		}
	}
	return User("");
}

int find_user_index_by_completedTime(std::vector<User> all_users , int time){
	for(int i = 0 ; i < all_users.size() ; i++){
		if(all_users[i].time_completed_tasks() == time){
			return i;
		}
	}
	return -1;
}

std::string UTrelloInterface::printUsersByPerformance(){
	std::vector<int> all_times;
	std::vector<User> all_users_copy = all_users;
	std::string return_message = "";
	for(int i = 0 ; i < all_users_copy.size() ; i++){
		all_times.push_back(all_users_copy[i].time_completed_tasks());
	}
	std::sort(all_times.begin() , all_times.end());
	for(int i = all_times.size() - 1 ; i >= 0 ; i--){
		return_message = return_message + find_user_by_completedTime(all_users_copy , all_times[i]).get_name() + "\n";
		all_users_copy.erase(all_users_copy.begin() + find_user_index_by_completedTime(all_users_copy , all_times[i]));
	}
	return return_message;
}