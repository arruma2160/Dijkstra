#include <iostream>
#include "elements.hpp"

int main(void)
{
    vector<vector<int>> matrix {
        {0,10,20, 0, 0,0},
        {0, 0, 0,50,10,0},
        {0, 0, 0,20,33,0},
        {0, 0, 0, 0,20,2},
        {0, 0, 0, 0, 0,1},
        {0, 0, 0, 0, 0,0},
    };
    Graph   graph{matrix};
    int start_id = 0;
    int end_id = 5;
    Dijkstra dijkstra {graph, start_id, end_id};
    stack<int> solution = dijkstra.solve_shortest_path();

    int id;
    while(!solution.empty())
    {
        id = solution.top(); 
        solution.pop();
        std::cerr << id << " "; 
    }
    std::cerr << std::endl;

    return 0;
}
