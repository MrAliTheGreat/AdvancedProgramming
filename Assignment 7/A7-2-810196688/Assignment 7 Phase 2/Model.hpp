#ifndef __MODEL_H__
#define __MODEL_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>

#define NUM_ROWS_HEADER 1
#define GOOD_STATUS "good"
#define BAD_STATUS "bad"
#define OUTPUT_FILENAME "output.txt"

double find_status_value(std::unordered_map<std::string , double>& trainset_info , std::string word){
	if(trainset_info.find(word) == trainset_info.end()){
		return 0;
	}else if(trainset_info[word] == 0){
		return 0;
	}
	return log10(trainset_info[word]);
}

std::unordered_map<std::string , double> trainset_extractor(std::string address , std::string status){
	std::unordered_map<std::string , double> trainset_info; 
	std::vector<std::string> extracted;
	std::stringstream ss_line;
	std::string line , info;
	int counter_line = 1;
	std::fstream file(address);

	if(!file.is_open()){
		throw file_existance_error();
	}

	while(getline(file , line)){
		ss_line.str(line);
		ss_line.clear();
		if(counter_line > NUM_ROWS_HEADER){
			while(getline(ss_line , info , ',')){
				extracted.push_back(info);
			}
		}else{
			counter_line++;
			continue;
		}
		if(status == GOOD_STATUS){
			trainset_info[extracted[0]] = std::stod(extracted[1]);
		}else if(status == BAD_STATUS){
			trainset_info[extracted[0]] = std::stod(extracted[2]);
		}
		extracted.clear();
		counter_line++;
	}
	file.close();
	return trainset_info;
}

double good_probability_extractor(std::string address){
	double good_probability;
	std::string info;
	std::fstream file(address);

	if(!file.is_open()){
		throw file_existance_error();
	}

	while(getline(file , info)){
		good_probability = std::stod(info);
	}

	file.close();
	return good_probability;
}

double calculate_accuracy(std::vector<int>& model_results , std::vector<int>& testset_labels){
	int correct = 0;
	for(int i = 0 ; i < model_results.size() ; i++){
		if(model_results[i] == testset_labels[i]){
			correct++;
		}
	}
	return ((double) correct / testset_labels.size()) * 100;
}

double calculate_recall(std::vector<int>& model_results , std::vector<int>& testset_labels){
	int correct_goods_model = 0;
	int correct_goods_testset = 0;
	for(int i = 0 ; i < model_results.size() ; i++){
		if(model_results[i] == testset_labels[i] && testset_labels[i] == 0){
			correct_goods_model++;
		}
		if(testset_labels[i] == 0){
			correct_goods_testset++;
		}
	}
	return ((double) correct_goods_model / correct_goods_testset) * 100;	
}

double calculate_precision(std::vector<int>& model_results , std::vector<int>& testset_labels){
	int correct_goods_model = 0;
	int goods_model = 0;
	for(int i = 0 ; i < model_results.size() ; i++){
		if(model_results[i] == testset_labels[i] && testset_labels[i] == 0){
			correct_goods_model++;
		}
		if(model_results[i] == 0){
			goods_model++;
		}
	}
	return ((double) correct_goods_model / goods_model) * 100;
}

void calculate_model_properties(std::string address , std::unordered_map<std::string , double>& trainset_good_info ,
								std::unordered_map<std::string , double>& trainset_bad_info , double good_probability){

	std::vector<int> model_results;
	std::vector<int> testset_labels;
	std::stringstream ss_line;
	std::string line , info;
	int counter_line = 1;
	double good_value = 0;
	double bad_value = 0;
	std::string word;

	std::fstream file(address);

	if(!file.is_open()){
		throw file_existance_error();
	}

	while(getline(file , line)){
		ss_line.str(line);
		ss_line.clear();
		if(counter_line > NUM_ROWS_HEADER){
			std::string comment = line.substr(0, line.size() - 2);
			int label = line[line.size() - 1] == '1' ? 1 : 0;

			testset_labels.push_back(label);
		    std::size_t current, previous = 0;
    		current = comment.find(' ');

			while (current != std::string::npos) {
				word = comment.substr(previous, current - previous);
				previous = current + 1;
        		current = comment.find(' ', previous);
				good_value += find_status_value(trainset_good_info , word);
				bad_value += find_status_value(trainset_bad_info , word);
			}
			if(abs(good_value + log10(good_probability)) >= abs(bad_value + log10(1 - good_probability))){
				model_results.push_back(0);
			}else{
				model_results.push_back(1);
			}
			good_value = 0;
			bad_value = 0;
		}
		counter_line++;
	}
	file.close();

	std::ofstream output_file(OUTPUT_FILENAME);
	output_file << "Recall: " << calculate_recall(model_results , testset_labels) << "\n";
	output_file << "Precision: " << calculate_precision(model_results , testset_labels) << "\n";
	output_file << "Accuracy: " << calculate_accuracy(model_results , testset_labels) << "\n";
	output_file.close();
}

int calculate_status_single_comment(std::string comment , std::unordered_map<std::string , double>& trainset_good_info ,
									std::unordered_map<std::string , double>& trainset_bad_info , double good_probability){

	std::vector<int> model_results;
	double good_value = 0;
	double bad_value = 0;
	std::stringstream ss_comment;
	ss_comment.str(comment);
	ss_comment.clear();

	std::string word;
	while(getline(ss_comment , word , ' ')){
		std::cout << word << "\n";
		good_value += find_status_value(trainset_good_info , word);
		bad_value += find_status_value(trainset_bad_info , word);
	}
	if(abs(good_value + log10(good_probability)) >= abs(bad_value + log10(1 - good_probability)) ){
		return 0;
	}
	return 1;
}

#endif