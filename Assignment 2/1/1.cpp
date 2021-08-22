#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int convertToInt(char digit_char){
	return digit_char - '0';
}

int convertBase6toBase10(int index , string numberBase10){
	int single_digit = convertToInt(numberBase10[(numberBase10.length() - 1) - index]);
	if(index >= numberBase10.length() - 1){
		return single_digit * pow(6 , index);
	}
	return (single_digit * pow(6 , index)) + convertBase6toBase10(index + 1 , numberBase10);
}

int main(){
	string input_number;
	cout << "Please Enter Your Number In Base 6 Here: ";
	cin >> input_number;
	cout << "Your Number In Base 10 : " << convertBase6toBase10(0 , input_number) << endl;
	return 0;
}