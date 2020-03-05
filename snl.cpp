#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>

std::vector<std::vector<int>> * create_transition_matrix(int board_size, std::unordered_map<int, int> snakes, std::unordered_map<int, int> ladders){
	static std::vector<std::vector<int>> transition_matrix;
	for (int board_position = 1; board_position != board_size+1; ++board_position){
		std::vector<int> new_positions;
		for (int num_rolled = 1; num_rolled != 7; ++num_rolled){
			new_positions.push_back(std::min(board_position+num_rolled, board_size));
		}
		transition_matrix.push_back(new_positions);
	}
	return &transition_matrix;
}

void print_transition_matrix(std::vector<std::vector<int>> * transition_matrix){
	for(std::vector<std::vector<int>>::iterator it = transition_matrix->begin(); it != transition_matrix->end(); ++it){
		for(std::vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			std::cout << *(it2) << " ";
		}
		std::cout << "\n";
	}
}

int main(int argc, char** argv){
	int board_size = 10;
	std::unordered_map<int, int> snakes;
	std::unordered_map<int, int> ladders;
	std::vector<std::vector<int>> * transition_matrix = create_transition_matrix(board_size, snakes, ladders);
	print_transition_matrix(transition_matrix);
}