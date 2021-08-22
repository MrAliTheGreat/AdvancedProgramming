#include "utrello_interface.hpp"
#include <stdexcept>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "utrello_interface.hpp"

TEST_CASE("`Output` test") {
	UTrelloInterface interface;

	interface.addUser("person_A");
	interface.addUser("person_B");
	interface.addUser("person_C");
	interface.addUser("person_D");

	interface.addList("List A");
	interface.addList("List B");
	interface.addList("List C");
	interface.addList("List D");

	interface.addTask("List A" , "Task A1" , 10 , 1 , "First Task A");
	interface.addTask("List A" , "Task A2" , 20 , 5 , "Second Task A");
	interface.addTask("List B" , "Task B1" , 15 , 6 , "First Task B");
	interface.addTask("List B" , "Task B2" , 10 , 3 , "Second Task B");
	interface.addTask("List B" , "Task B3" , 10 , 3 , "Third Task B");
	interface.addTask("List C" , "Task C1" , 30 , 10 , "First Task C");

	interface.assignTask("Task A1" , "person_A");
	interface.assignTask("Task A2" , "person_B");
	interface.assignTask("Task B1" , "person_A");
	interface.assignTask("Task B2" , "person_A");
	interface.assignTask("Task C1" , "person_C");

	interface.completeTask("Task A2");
	interface.completeTask("Task B1");
	interface.completeTask("Task C1");

	REQUIRE(interface.printTotalEstimatedTime() == 35);
	REQUIRE(interface.printTotalRemainingTime() == 20);
	REQUIRE(interface.printUserWorkload("person_A") == 35);
	REQUIRE(interface.printUserWorkload("person_Z") == 0);
	REQUIRE(interface.printTask("Task A1") == "Task A1\nFirst Task A\nPriority: 1\nEstimated Time: 10\nAssigned to person_A\n");
	REQUIRE(interface.printList("List C") == "List List C\n10 | Task C1 | person_C | 30h\n");
	REQUIRE(interface.printAllLists() == "List List A\n1 | Task A1 | person_A | 10h\n5 | Task A2 | person_B | 20h\n\nList List B\n6 | Task B1 | person_A | 15h\n3 | Task B2 | person_A | 10h\n3 | Task B3 | Unassigned | 10h\n\nList List C\n10 | Task C1 | person_C | 30h\n\nList List D\n\n");
	REQUIRE(interface.printUserTasks("person_Z") == "User does not exist");
	REQUIRE(interface.printUserTasks("person_B") == "5 | Task A2 | person_B | 20h\n");
	REQUIRE(interface.printUserUnfinishedTasks("person_A") == "1 | Task A1 | person_A | 10h\n3 | Task B2 | person_A | 10h\n");
	REQUIRE(interface.printUnassignedTasksByPriority() == "3 | Task B3 | ‫‪Unassigned‬‬ | 10h\n");
	REQUIRE(interface.printAllUnfinishedTasksByPriority() == "1 | Task A1 | person_A | 10h\n3 | Task B2 | person_A | 10h\n3 | Task B3 | ‫‪Unassigned‬‬ | 10h\n");
	REQUIRE(interface.printUsersByWorkload() == "person_D\nperson_B\nperson_C\nperson_A\n");

	//REQUIRE(interface.printUserWorkload("person_Z") == 0);
	//REQUIRE(interface.printUserWorkload("person_Z") == 0);

}