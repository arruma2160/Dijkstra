#include <iostream>
#include "elements.hpp"

int main(void)
{
    vector<vector<int>> matrix {
       //  0,  1,  2,  3,  4,  5,  6,  7
        {  0,  3,  2,  5,  0,  0,  0,  0}, //0
        {  3,  0,  0,  0,  3,  0,  0,  0}, //1
        {  2,  0,  0,  0,  1,  6,  0,  0}, //2
        {  5,  0,  0,  2,  0,  0,  0,  0}, //3
        {  3,  0,  1,  0,  0,  0,  4,  0}, //4
        {  0,  0,  6,  2,  0,  0,  1,  4}, //5
        {  0,  0,  0,  0,  4,  1,  0,  2}, //6
        {  0,  0,  0,  0,  0,  4,  2,  0}  //7
    };
    Graph   graph{matrix};
    int start_id = 0;
    int end_id = 7;
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
