#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>

std::vector<std::vector<int>> * create_transition_matrix(int board_size, std::unordered_map<int, int> * snakes, std::unordered_map<int, int> * ladders){
	static std::vector<std::vector<int>> transition_matrix;
	for (int board_position = 1; board_position != board_size+1; ++board_position){
		std::vector<int> new_positions;
		for (int num_rolled = 1; num_rolled != 7; ++num_rolled){
			std::unordered_map<int, int>::const_iterator snakes_it = snakes->find(board_position+num_rolled);
		    std::unordered_map<int, int>::const_iterator ladders_it = ladders->find(board_position+num_rolled);
			if (snakes_it != snakes->end()){
				new_positions.push_back(snakes_it->second);	
			}
			else if (ladders_it != ladders->end()){
				new_positions.push_back(ladders_it->second);
			}
			else{
				new_positions.push_back(std::min(board_position+num_rolled, board_size));
			}
		}
		transition_matrix.push_back(new_positions);
	}
	return &transition_matrix;
}

void print_transition_matrix(std::vector<std::vector<int>> * transition_matrix){
	for (std::vector<std::vector<int>>::iterator it = transition_matrix->begin(); it != transition_matrix->end(); ++it){
		for (std::vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			std::cout << *(it2) << " ";
		}
		std::cout << "\n";
	}
}

std::set<int> * possible_previous_squares(int current_square, std::vector<std::vector<int>> * transition_matrix){
	static std::set<int> possible_previous_squares;
	std::set<int>::iterator set_it = possible_previous_squares.begin();
	int previous_square = 1;
	for (std::vector<std::vector<int>>::iterator it = transition_matrix->begin(); it != transition_matrix->end(); ++it){
		for (std::vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			if ((*it2) == current_square){
				possible_previous_squares.insert(set_it, previous_square);
			}
		}
		++previous_square;
	}
	return &possible_previous_squares;
}

void print_possible_previous_squares(int current_square, std::vector<std::vector<int>> * transition_matrix){
	std::set<int> * possible_previous_test = possible_previous_squares(current_square, transition_matrix);
	for(std::set<int>::iterator it = possible_previous_test->begin(); it != possible_previous_test->end(); ++it){
		std::cout << (*it) << " ";
	}
	std::cout << "\n";
}

int main(int argc, char** argv){
	int board_size = 10;
	std::unordered_map<int, int> snakes = {};
	std::unordered_map<int, int> ladders = {};
	std::vector<std::vector<int>> * transition_matrix = create_transition_matrix(board_size, (&snakes), (&ladders));
	print_transition_matrix(transition_matrix);
	print_possible_previous_squares(5, transition_matrix);
}