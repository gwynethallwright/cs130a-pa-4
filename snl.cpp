#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <queue>
#include <list>
#include <stack>

struct queue_entry{ 
    int square_number;
    int distance_from_start;
    int type_of_square;
    int original_square;
    queue_entry* next_node;
};

int return_minimum_throws(int start_square, int end_square, int board_size, std::unordered_map<int, int> * snakes, std::unordered_map<int, int> * ladders){
	std::unordered_map<int, bool> visited;
	for (int i = 1; i < board_size+1; ++i){
		visited.insert({{i, false}});
	}
	std::queue<queue_entry*> bfs_queue;
	visited[start_square] = true;
	queue_entry start = {start_square, 0, 0, 0, nullptr};
    bfs_queue.push(&start);
    queue_entry* current;
    while (!bfs_queue.empty())
    { 
        current = bfs_queue.front();
        int board_position = current->square_number;
        if (board_position == end_square){
            break; 
        }
        bfs_queue.pop();
        for (int j = current->square_number+6; j > current->square_number; --j)
        {
            if (j <= board_size){
            	if (!visited[j]){
            		queue_entry* new_entry = (queue_entry*) malloc(sizeof(queue_entry));
            		new_entry->distance_from_start = current->distance_from_start+1;
            		new_entry->original_square = j;
                	visited[j] = true;
                	std::unordered_map<int, int>::const_iterator snakes_it = snakes->find(j);
		    		std::unordered_map<int, int>::const_iterator ladders_it = ladders->find(j);
					if (ladders_it != ladders->end()){
						new_entry->square_number = ladders_it->second;
						new_entry->type_of_square = 1;
					}
					else if (snakes_it != snakes->end()){
						new_entry->square_number = snakes_it->second;
						new_entry->type_of_square = -1;
					}
					else{
						new_entry->square_number = j;
						new_entry->type_of_square = 0;
					}
					new_entry->next_node = current;
					bfs_queue.push(new_entry);
            	}
            }
        }
    }
    queue_entry* iterate_thru = current;
    std::stack <std::string> path;
    std::string output;

    while (iterate_thru->next_node != nullptr){
    	if (iterate_thru->type_of_square == 1){
    		output = (std::to_string(iterate_thru->original_square)).append("+");
    	}
    	else if (iterate_thru->type_of_square == -1){
    		output = (std::to_string(iterate_thru->original_square)).append("-");
    	}
    	else {
    		output = "";
    	}
    	output = output.append(std::to_string(iterate_thru->square_number));
    	path.push(output);
    	iterate_thru = iterate_thru->next_node;
	}
	std::cout << "1 ";
	while (!path.empty()){
		std::cout << path.top() << " ";
		path.pop();
	}
	std::cout << "\n";
    return current->distance_from_start;
}

int main(int argc, char** argv){

	std::string the_input = argv[1];
	std::stringstream ss(the_input);
  	std::string parse_to;

  	std::getline(ss, parse_to, '\n');
  	int num_cases = std::stoi(parse_to);

  	for (int game_num = 1; game_num < num_cases+1; ++game_num){

  		std::getline(ss, parse_to, '\n');
  		std::stringstream ss_line_1(parse_to);

  		std::string board_size_str;
  		std::getline(ss_line_1, board_size_str, ' ');
  		std::string num_snakes_str;
  		std::getline(ss_line_1, num_snakes_str, ' ');
  		std::string num_ladders_str;
  		std::getline(ss_line_1, num_ladders_str, ' ');

  		int board_size = std::stoi(board_size_str)*std::stoi(board_size_str);
  	  	int num_snakes = std::stoi(num_snakes_str);
  		int num_ladders = std::stoi(num_ladders_str);

		std::unordered_map<int, int> snakes = {};
		std::unordered_map<int, int> ladders = {};

		std::string start;
		std::string end;
		std::getline(ss, parse_to, '\n');
		std::stringstream ss_line_2(parse_to);

		for (int i = 0; i < 2*num_ladders; ++i){
			std::getline(ss_line_2, start, ' ');
			std::getline(ss_line_2, end, ' ');
			ladders.insert({{std::stoi(start), std::stoi(end)}});
		}

		std::getline(ss, parse_to, '\n');
		std::stringstream ss_line_3(parse_to);

		for (int i = 0; i < 2*num_snakes; ++i){
			std::getline(ss_line_3, start, ' ');
			std::getline(ss_line_3, end, ' ');
			snakes.insert({{std::stoi(start), std::stoi(end)}});
		}

		int min_throws = return_minimum_throws(1, board_size, board_size, &snakes, &ladders);
		std::cout << min_throws << "\n";
  	}
}