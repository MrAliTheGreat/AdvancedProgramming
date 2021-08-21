#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){
	string input_number;
	vector<string> vec_numbers;
	int counter = 0 , counter_wrong = 0;

	while(cin >> input_number){
		vec_numbers.push_back(input_number);
	}

	for(int i = 0 ; i < vec_numbers.size() ; i++){
		for(int j = 0 ; j < vec_numbers.size() ; j++){
			if(vec_numbers[i] == vec_numbers[j]){
				counter++;
			}
		}
		if(counter < 2){
			cout << vec_numbers[i];
			counter_wrong++;
		}
		counter = 0;
	}
	if(counter_wrong == 0){
		cout << 0;
	}
	return 0 ;
}