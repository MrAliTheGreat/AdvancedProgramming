#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#define NUM_ROWS_HEADER 1
#define NUM_COLUMNS_CLASSIFIER 3
#define NUM_DATA_PARAMS 2
#define SAMPLE_FORMAT "/classifier_1.csv"

using namespace std;

void vector_printer_double(vector<double> input_vector){
	for(int i = 0 ; i < input_vector.size() ; i++){
		cout << input_vector[i] << " ";
	}
	cout << endl;
}

void vector_printer_int(vector<int> input_vector){
	for(int i = 0 ; i < input_vector.size() ; i++){
		cout << input_vector[i] << " ";
	}
	cout << endl;
}

vector<double> extractor(string address){
	vector<double> extracted;
	stringstream ss_line;
	string line , number;
	int counter_line = 1;
	fstream file(address);

	while(getline(file , line)){
		ss_line.str(line);
		ss_line.clear();
		if(counter_line > NUM_ROWS_HEADER){
			while(getline(ss_line , number , ',')){
				extracted.push_back(stod(number));
			}
		}
		counter_line++;
	}
	file.close();
	return extracted;
}

vector<double> extract_dataset(string address){
	return extractor(address);
}

vector<double> extract_weights(string address){
	return extractor(address);
}

vector<int> extract_labels(string address){
	int counter_line = 1;
	string label;
	vector<int> labels;
	fstream label_file(address);

	while(getline(label_file , label)){
		if(counter_line > NUM_ROWS_HEADER){
			labels.push_back(stoi(label));	
		}
		counter_line++;
	}
	return labels;
}

bool is_extractable(string address){
	fstream file_weight(address);
	if(!file_weight.is_open()){
		file_weight.close();
		return false;
	}
	file_weight.close();
	return true;
}

int find_max_position(vector<double> input_vector){
	int max_pos = 0;
	double max_value;
	for(int i = 0 ; i < input_vector.size() ; i++){
		if(input_vector[i] > max_value){
			max_value = input_vector[i];
			max_pos = i;
		}
	}
	return max_pos;
}

int get_num_classes(string address){
	string line;
	int counter_line = 0;
	fstream file(address);

	while(getline(file , line)){
		counter_line++;
	}
	file.close();
	return counter_line - 1;
}

int find_most_common(vector<int> input_vector , int max_number){
	int max_count = 0 , element_count = 0 , element_value;
	for(int i = 0 ; i < max_number ; i++){
		element_count = count(input_vector.begin() , input_vector.end() , i);
		if(element_count > max_count){
			max_count = element_count;
			element_value = i;
		}else if(element_count == max_count && i < element_value){
			max_count = element_count;
			element_value = i;
		}
	}
	return element_value;
}

double score_computation(double B0 , double B1 , double bias , double length , double width){
	return B0 * length + B1 * width + bias;
}

vector<int> dataset_classifier(vector<double> classifier , vector<double> dataset){
	vector<double> scores;
	vector<int> classes;
	for(int i = 0 ; i < dataset.size() ; i += NUM_DATA_PARAMS){
		for(int j = 0 ; j < classifier.size() ; j += NUM_COLUMNS_CLASSIFIER){
			scores.push_back(score_computation(classifier[j] , classifier[j + 1] , classifier[j + 2] , dataset[i] , dataset[i + 1]));
		}
		classes.push_back(find_max_position(scores));
		scores.clear();
	}
	return classes;
}

vector<int> determine_dataset_classifications(vector<vector<int> > all_classes , int dataset_size , int count_classes){
	vector<int> single_data_classes , final_classes;
	for(int i = 0 ; i < dataset_size ; i++){
		for(int j = 0 ; j < all_classes.size() ; j++){
			single_data_classes.push_back(all_classes[j][i]);
		}
		final_classes.push_back(find_most_common(single_data_classes , count_classes));
		single_data_classes.clear();
	}
	return final_classes;
}

double compute_correctness_percentage(vector<int> dataset_classifications , vector<int> correct_labels){
	double corrects_count = 0;
	for(int i = 0 ; i < correct_labels.size() ; i++){
		if(dataset_classifications[i] == correct_labels[i]){
			corrects_count++;
		}
	}
	return (corrects_count / correct_labels.size()) * 100;
}



int main(int argc , char* argv[]){
	string validation_dataset_path = argv[1];
	string weight_path = argv[2];
	int file_number = 0;

	vector<double> weights , dataset;
	vector<vector<int> > all_classes;
	vector<int> dataset_classifications , correct_labels;

	dataset = extract_dataset(validation_dataset_path + "/dataset.csv");

	while(is_extractable(weight_path + "/classifier_" + to_string(file_number) + ".csv")){
		weights = extract_weights(weight_path + "/classifier_" + to_string(file_number) + ".csv");
		all_classes.push_back(dataset_classifier(weights , dataset));
		file_number++;
	}

	int count_classes = get_num_classes(weight_path + SAMPLE_FORMAT);

	dataset_classifications = determine_dataset_classifications(all_classes , dataset.size() / NUM_DATA_PARAMS , count_classes);
	correct_labels = extract_labels(validation_dataset_path + "/labels.csv");
	cout << "Accuracy: ";
	printf("%.2f\n" , compute_correctness_percentage(dataset_classifications , correct_labels));
	return 0;
}