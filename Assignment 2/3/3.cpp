#include<iostream>
#include<string>
#include<vector>

using namespace std;

void vector_printer(vector<int> input_vec){
	for (int i = 0; i < input_vec.size(); i++){
		cout << input_vec[i] << " ";
	}
}

void vector_printer_2D(vector<vector<string> > input_vec){
	for (int i = 0; i < input_vec.size(); i++){
		for (int j = 0; j < input_vec[i].size(); j++){
			cout << input_vec[i][j] << " ";
		}
		cout << endl;
	}
}

void vector_printer_2D_i(vector<vector<int> > input_vec){
	for (int i = 0; i < input_vec.size(); i++){
		for (int j = 0; j < input_vec[i].size(); j++){
			cout << input_vec[i][j] << " ";
		}
		cout << endl;
	}
}

void create_mine_region(vector<vector<int> >& board , int pos_x , int pos_y ,int num_row , int num_column){
	if((pos_x < num_row) && (pos_x >= 0) && (pos_y < num_column) && (pos_y >= 0)){
		if(board[pos_x][pos_y] != -1){
			board[pos_x][pos_y]++;
		}
	}
}

bool is_previous(vector<vector<int> > board , int num_row , int num_column){
	if(board[num_row][num_column] == -2){
		return true;
	}
	return false;
}

bool is_mine_related(vector<vector<int> > board , int num_row , int num_column){
	if(board[num_row][num_column] > 0){
		return true;
	}
	return false;
}

bool is_mine(vector<vector<int> > board , int num_row , int num_column){
	if(board[num_row][num_column] == -1){
		return true;
	}
	return false;
}


bool is_valid_pos(vector<vector<int> > board , int pos_x , int pos_y ,int num_row , int num_column){
	if((pos_x < num_row) && (pos_x >= 0) && (pos_y < num_column) && (pos_y >= 0)){
		return true;
	}
	return false;
}

vector<int> combine_vectors(vector<int> base , vector<int> added){
	for(int i = 0 ; i < added.size() ; i++){
		base.push_back(added[i]);
	}
	return base;
}

vector<vector<int> > find_path(vector<vector<int> > board , int pos_x , int pos_y, int num_row , int num_column){

	board[pos_x][pos_y] = -2;

	if(is_valid_pos(board , pos_x , pos_y + 1 , num_row , num_column) && !is_previous(board , pos_x , pos_y + 1) && !is_mine(board , pos_x , pos_y + 1)){
		if(!is_mine_related(board , pos_x , pos_y + 1)){
			board = find_path(board , pos_x , pos_y + 1 , num_row , num_column);
		}else{
			board[pos_x][pos_y + 1] = -2;
		}
	}
	if(is_valid_pos(board , pos_x , pos_y - 1 , num_row , num_column) && !is_previous(board , pos_x , pos_y - 1) && !is_mine(board , pos_x , pos_y - 1)){
		if(!is_mine_related(board , pos_x , pos_y - 1)){
			board = find_path(board , pos_x , pos_y - 1 , num_row , num_column);
		}else{
			board[pos_x][pos_y - 1] = -2;
		}
	}
	if(is_valid_pos(board , pos_x - 1 , pos_y , num_row , num_column) && !is_previous(board , pos_x - 1 , pos_y) && !is_mine(board , pos_x - 1 , pos_y)){
		if(!is_mine_related(board , pos_x - 1 , pos_y)){
			board = find_path(board , pos_x - 1, pos_y , num_row , num_column);
		}else{
			board[pos_x - 1][pos_y] = -2;
		}
		
	}
	if(is_valid_pos(board , pos_x + 1 , pos_y , num_row , num_column) && !is_previous(board , pos_x + 1 , pos_y) && !is_mine(board , pos_x + 1 , pos_y)){
		if(!is_mine_related(board , pos_x + 1 , pos_y)){
			board = find_path(board , pos_x + 1, pos_y , num_row , num_column);
		}else{
			board[pos_x + 1][pos_y] = -2;
		}
	}

	if(is_valid_pos(board , pos_x + 1 , pos_y + 1 , num_row , num_column) && !is_previous(board , pos_x + 1 , pos_y + 1) && !is_mine(board , pos_x + 1 , pos_y + 1)){
		if(is_mine_related(board , pos_x + 1 , pos_y + 1)){
			board[pos_x + 1][pos_y + 1] = -2;
		}
	}

	if(is_valid_pos(board , pos_x + 1 , pos_y - 1 , num_row , num_column) && !is_previous(board , pos_x + 1 , pos_y - 1) && !is_mine(board , pos_x + 1 , pos_y - 1)){
		if(is_mine_related(board , pos_x + 1 , pos_y - 1)){
			board[pos_x + 1][pos_y - 1] = -2;
		}
	}

	if(is_valid_pos(board , pos_x - 1 , pos_y - 1 , num_row , num_column) && !is_previous(board , pos_x - 1 , pos_y - 1) && !is_mine(board , pos_x - 1 , pos_y - 1)){
		if(is_mine_related(board , pos_x - 1 , pos_y - 1)){
			board[pos_x - 1][pos_y - 1] = -2;
		}
	}

	if(is_valid_pos(board , pos_x - 1 , pos_y + 1 , num_row , num_column) && !is_previous(board , pos_x - 1 , pos_y + 1) && !is_mine(board , pos_x + 1 , pos_y + 1)){
		if(is_mine_related(board , pos_x - 1 , pos_y + 1)){
			board[pos_x - 1][pos_y + 1] = -2;
		}
	}

	return board;
	
}



int main(){

	vector<string> vec_info;
	vector<string> vec_board;
	vector<vector<string> > string_board;
	vector<vector<int> > int_vec_board(vec_board.size());
	vector<int> int_row;
	vector<int> pos_mines;
	string info;
	int counter = 0;

	//cout << "Please Enter Your Info: ";
	while(cin >> info){
		if(counter < 4){
			vec_info.push_back(info);
		}else{
			vec_board.push_back(info);
		}
		counter++;
	}

	for(int i = 0 ; i < vec_board.size() ; i++){
		for(int j = 0 ; j < vec_board[i].length() ; j++){
			if(vec_board[i][j] == '.'){
				int_row.push_back(0);
			}else{
				int_row.push_back(-1);
				pos_mines.push_back(i);
				pos_mines.push_back(j);
			}
		}
		int_vec_board.push_back(int_row);
		int_row.clear();
	}

	int number_rows = stoi(vec_info[0]) , number_columns = stoi(vec_info[1]);

	for(int i = 0 ; i < pos_mines.size() ; i+=2){
		create_mine_region(int_vec_board , pos_mines[i] + 1 , pos_mines[i+1] - 1 , number_rows , number_columns);
		create_mine_region(int_vec_board , pos_mines[i] , pos_mines[i+1] - 1 , number_rows , number_columns);
		create_mine_region(int_vec_board , pos_mines[i] - 1 , pos_mines[i+1] - 1 , number_rows , number_columns);
		create_mine_region(int_vec_board , pos_mines[i] - 1 , pos_mines[i+1] , number_rows , number_columns);
		create_mine_region(int_vec_board , pos_mines[i] - 1, pos_mines[i+1] + 1 , number_rows , number_columns);
		create_mine_region(int_vec_board , pos_mines[i] , pos_mines[i+1] + 1 , number_rows , number_columns);
		create_mine_region(int_vec_board , pos_mines[i] + 1 , pos_mines[i+1] + 1 , number_rows , number_columns);
		create_mine_region(int_vec_board , pos_mines[i] + 1, pos_mines[i+1] , number_rows , number_columns);
	}

	int chosen_x = stoi(vec_info[3]) - 1 , chosen_y = stoi(vec_info[2]) - 1;
	vector<vector<int> > path_board = int_vec_board;

	if(int_vec_board[chosen_x][chosen_y] > 0){
		path_board[chosen_x][chosen_y] = -2;
	}else{
		path_board = find_path(int_vec_board , chosen_x , chosen_y, number_rows , number_columns);
	}

//	vector_printer_2D_i(path_board);
//	cout << "========================" << endl;

	vec_board.clear();

	for(int i = 0 ; i < number_rows ; i++){
		for(int j = 0 ; j < number_columns ; j++){
			if(path_board[i][j] == -2){
				vec_board.push_back(to_string(int_vec_board[i][j]));
			}else{
				vec_board.push_back("*");
			}
		}
		string_board.push_back(vec_board);
		vec_board.clear();
	}
	
	//string_board[chosen_x][chosen_y] = 'X';

	vector_printer_2D(string_board);

	//cout << "========================" << endl;
	//vector_printer_2D_i(int_vec_board);

	return 0;
}