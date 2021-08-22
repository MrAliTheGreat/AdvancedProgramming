#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// This is for printing the relations at first
void vector_printer_2D(vector<vector<string> > vec){
	cout << "All Relations (Two Way Relations):" << endl;
	for(int i = 0 ; i < vec.size() ; i++){
		cout << i << " : ";
		for(int j = 0 ; j < vec[i].size() ; j++){
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	// line: This is for getting every line of relations from people.txt
	// member: This is for every part of each line in people.txt
	// ss_line: A stringstream used for taking away the spaces
	// num_members: Number of all the members
	// index: number of each person
	// flag: This is used for excluding the person from his or her relations

	string line;
	string member;
	stringstream ss_line;
	int num_members = 0 , index = 0 , flag = 1;

	// Creating file of people.txt
	fstream myfile ("people.txt");

	// This is for getting the number of members
	while(getline(myfile , line)){
		num_members++;
	}

	// Here after reading the file for once we are at the end
	// We have to first clear EOF
	// Then put like the cursor at the first location of the file
	myfile.clear();
	myfile.seekg(0);

	// This is a 2D vector with every index of the first dimension being the people
	// and the second dimension being their relations
	vector<vector<string> > relations(num_members);

	// This is for putting all the relations in the relations vector
	while(getline(myfile , line)){
		ss_line.str(line);
		ss_line.clear();
		while(getline(ss_line , member , ' ')){
			if(flag != 1){
				relations[index].push_back(member);
				relations[stoi(member)].push_back(to_string(index));
			}
			flag++;
		}
		flag = 1;
		index++;
	}
	
	// Printing the relations in the terminal
	//vector_printer_2D(relations);

	// Closing people.txt
	myfile.close();


	// From this part forward we will have the commands
	//cout << "Your Commands Here: " << endl;

	// flag_fail: This is used for the people with no relations to print out Failed!
	// fail: This is for incorrect inputs to print out Failed!
	// whole_message: All the sentence that the user enters
	// part_message: This is all the components of the sentence with each part seperated
	// sentence: The message that the user sends to another person
	// show_line: This is for show_msg command
	// vec_message: Vector of all the components of user's input
	// whole_line: Stringstream used for seperating the components
	// message_file: Message file that we create for each person
	// show_file: File that we show for show_msg command
	int flag_fail = 0 , fail = 0;
	string whole_message , part_message , sentence = "" , show_line;
	vector<string> vec_message;
	stringstream whole_line;
	fstream message_file;
	ifstream show_file;

	// Seperating the components and putting them in a vector
	while(getline(cin , whole_message)){

		whole_line.str(whole_message);
		whole_line.clear();

		while(getline(whole_line , part_message , ' ')){
			vec_message.push_back(part_message);
		}

		// This part is for show_msg part
		if(vec_message.size() == 2){
			// This part is checking the command that the user put in terminal
			if(vec_message[0] == "show_msg"){
				show_file.open(vec_message[1] + ".txt");
				// This part is for checking whether the file exist or not
				if(show_file.is_open()){
					while(getline(show_file , show_line)){
						cout << show_line << endl;
					}
				}else{
					cout << "Failed!" << endl;
					vec_message.clear();
				}
			}else{
			cout << "Failed!" << endl;
			vec_message.clear();
			}
			vec_message.clear();
			show_file.close();


		// This part is for sending messages
		}else if(vec_message.size() > 2){
			// This part is for composing the message and putting it in variable sentence
			for(int i = 2 ; i < vec_message.size() ; i++){
				sentence += vec_message[i] + " ";
			}
			// This part is for checking whether each part of the input is right or not
			for (int i = 0; i < vec_message[0].length(); i++){
				// Checking the sender
				if(!isdigit((vec_message[0][i]))){
					cout << "Failed!" << endl;
					fail = 1;
					vec_message.clear();
					break;
				}
			}
			if(fail == 1){
				fail = 0;
				continue;
			}else{
				for (int i = 0; i < vec_message[1].length(); i++){
					// checking the receiver
					if(!isdigit((vec_message[1][i]))){
						cout << "Failed!" << endl;
						fail = 1;
						vec_message.clear();
						break;
					}
				}
				if(fail == 1){
					fail = 0;
					continue;
				}
			}
			// This part is for members outside the range
			if((stoi(vec_message[0]) > relations.size() || stoi(vec_message[0]) < 0) || (stoi(vec_message[1]) > relations.size() || stoi(vec_message[1]) < 0)){
				cout << "Failed!" << endl;
				vec_message.clear();
				continue;
			}
			// This part is for omitting the spaces at the end of the message
			sentence.erase(sentence.find_last_not_of(" ") + 1);

			// This part is for making .txt files and putting the messages in them
			for(int i = 0 ; i < relations[stoi(vec_message[0])].size() ; i++){
				// Checking whether there is a relation or not
				if(relations[stoi(vec_message[0])][i] == vec_message[1]){
					message_file.open(vec_message[1] + ".txt" , ios::app);
					message_file << vec_message[0] << " " << sentence << endl;
					message_file.close();
					cout << "Sent!" << endl;
					flag_fail++;
				}else if(i == relations[stoi(vec_message[0])].size() - 1 && flag_fail == 0){
					cout << "Failed!" << endl;
				}
			}
			// This part is for when there is no relation at all
			if(relations[stoi(vec_message[0])].size() == 0){
				cout << "Failed!" << endl;
			}
			// Clearing and reseting everything for the next loop
			vec_message.clear();
			sentence = "";
			flag_fail = 0;
			message_file.close();
		// For any other situation printing out Failed!
		}else{
			cout << "Failed!" << endl;
			vec_message.clear();
		}
	}
	return 0;
}