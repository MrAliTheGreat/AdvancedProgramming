#include<iostream>
#include<string>
#include<vector>

using namespace std;

void print_vector(vector<string> numbers){
	for(int i = 0 ; i < numbers.size() ; i++){
		cout << numbers[i] << " ";
	}
	cout << endl;
}

vector<string> sorter(vector<string> v_number , string previous_number){
	string last_number = v_number.back();
	v_number.pop_back();

	if(v_number.size() <= 0){
		if(stoi(previous_number) > stoi(last_number)){
			v_number.push_back(last_number);
			v_number.push_back(previous_number);
			return v_number;
		}
		v_number.push_back(previous_number);
		v_number.push_back(last_number);
		return v_number;
	}

	v_number = sorter(v_number , last_number);
	if(previous_number != ""){
		if(stoi(previous_number) > stoi(v_number.back())){
			v_number.push_back(previous_number);
		}else{
			last_number = v_number.back();
			v_number.pop_back();
			v_number.push_back(previous_number);
			v_number.push_back(last_number);
		}
	}
	return v_number;
}

int main(){
	string input_number;
	vector<string> vec_numbers;
	while(cin >> input_number){
		vec_numbers.push_back(input_number);
	}

	for(int i = 0 ; i < vec_numbers.size(); i++){
		vec_numbers = sorter(vec_numbers , "");
	}

	print_vector(vec_numbers);	

	return 0;
}