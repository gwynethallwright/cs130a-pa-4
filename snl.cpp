#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <queue>

struct queue_entry{ 
    int square_number;
    int distance_from_start;
};

int return_minimum_throws(int start_square, int end_square, int board_size, std::unordered_map<int, int> * snakes, std::unordered_map<int, int> * ladders){
	std::unordered_map<int, bool> visited;
	for (int i = 1; i < board_size+1; ++i){
		visited.insert({{i, false}});
	}
	std::queue<queue_entry> bfs_queue;
	visited[start_square] = true;
	queue_entry start = {start_square, 0};
    bfs_queue.push(start);
    queue_entry current;
    while (!bfs_queue.empty())
    { 
        current = bfs_queue.front(); 
        int board_position = current.square_number;
        if (board_position == end_square){
            break; 
        }
        bfs_queue.pop(); 
        for (int j = current.square_number+1; j < current.square_number+7; ++j)
        {
            if (j < board_size){
            	if (!visited[j]){
            		queue_entry new_entry = {j, current.distance_from_start+1};
                	visited[j] = true; 
                	std::unordered_map<int, int>::const_iterator snakes_it = snakes->find(j);
		    		std::unordered_map<int, int>::const_iterator ladders_it = ladders->find(j);
					if (snakes_it != snakes->end()){
						new_entry.distance_from_start = snakes_it->second;
					}
					else if (ladders_it != ladders->end()){
						new_entry.distance_from_start = ladders_it->second;
					}
					bfs_queue.push(new_entry);
            	}
            }
        }
    }
    return current.distance_from_start;
}

int main(int argc, char** argv){
	int board_size = 10;
	int start_square = 1;
	int end_square = 10;
	std::unordered_map<int, int> snakes = {};
	std::unordered_map<int, int> ladders = {};
	std::cout << return_minimum_throws(start_square, end_square, board_size, &snakes, &ladders) << "\n";
}