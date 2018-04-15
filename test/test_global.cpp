#include <gtest/gtest.h>
#include "elements.hpp"

TEST(Edge, 1_Edge_creation)
{
    Edge edge {1, 2, 100};

    ASSERT_EQ(edge.fromNode(), 1);
    ASSERT_EQ(edge.toNode(), 2);
    ASSERT_EQ(edge.distance(), 100);
}

TEST(Edge, 2_Copy_of_Edges)
{
    Edge edge_1 {1, 2, 100};
    Edge edge_2 {edge_1};

    ASSERT_EQ(edge_2.fromNode(), 1);
    ASSERT_EQ(edge_2.toNode(), 2);
    ASSERT_EQ(edge_2.distance(), 100);
}

TEST(Edge, 3_Assignment_of_Edges)
{
    Edge edge_1 {1, 2, 100};
    Edge edge_2 {1, 3, 40};
    edge_2 = edge_1;

    ASSERT_EQ(edge_2.fromNode(), 1);
    ASSERT_EQ(edge_2.toNode(), 2);
    ASSERT_EQ(edge_2.distance(), 100);
}

TEST(Edge, 4_Sorting_priority_priority_queue)
{
    // Shortest distances -> Highest priority
    std::priority_queue<Edge> pq;
    pq.push({1,2,50});
    pq.push({1,2,80});
    pq.push({1,2,70});
    pq.push({1,2,90});
    pq.push({1,2,60});

    Edge top = pq.top();
    ASSERT_EQ(top.distance(), 50);
    pq.pop();

    top = pq.top();
    ASSERT_EQ(top.distance(), 60);
    pq.pop();

    top = pq.top();
    ASSERT_EQ(top.distance(), 70);
    pq.pop();

    top = pq.top();
    ASSERT_EQ(top.distance(), 80);
    pq.pop();

    top = pq.top();
    ASSERT_EQ(top.distance(), 90);
    pq.pop();
}


TEST(Node, 1_Node_s_edges_in_order_1)
{
    vector<int> distances {1,2,3,4,5};
    Node node {0, distances };

    vector<Edge> edges = node.all_edges();

    int i = 0;
    for(const auto& edge : edges)
    {
        ASSERT_EQ(edge.distance(), distances[i++]);
    }
}

TEST(Node, 2_Node_s_edges_in_order_2)
{
    vector<int> distances {5,4,3,2,1};
    vector<int> test_order {1,2,3,4,5};

    Node node {0, distances };
    vector<Edge> edges = node.all_edges();

    int i = 0;
    for(const auto& edge : edges)
    {
        ASSERT_EQ(edge.distance(), test_order[i++]);
    }
}

TEST(Node, 3_copy_const)
{
    vector<int> distances {5,4,3,2,1};
    vector<int> test_order {1,2,3,4,5};
    Node orig_node {0, distances };
    Node node {orig_node};
    vector<Edge> edges = node.all_edges();

    int i = 0;
    for(const auto& edge : edges)
    {
        ASSERT_EQ(edge.distance(), test_order[i++]);
    }
}

TEST(Graph, 1_Grap_creation)
{
    vector<vector<int>> matrix {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    bool exception_caught {false};
    Graph   graph{matrix};
    Node node_1 = graph.get_node(0);
    vector<Edge> edges_1 = node_1.all_edges();
    vector<int> test_1 = {1,2,3};
    Node node_2 = graph.get_node(1);
    vector<Edge> edges_2 = node_2.all_edges();
    vector<int> test_2 = {4,5,6};
    Node node_3 = graph.get_node(2);
    vector<Edge> edges_3 = node_3.all_edges();
    vector<int> test_3 = {7,8,9};

    try {
        Node node_4 = graph.get_node(4);
    } catch (std::logic_error) {
        exception_caught = true;
    }

    int i = 0;
    for(const auto& edge : edges_1)
    {
        ASSERT_EQ(edge.distance(), test_1[i++]);
    }
    i = 0;
    for(const auto& edge : edges_2)
    {
        ASSERT_EQ(edge.distance(), test_2[i++]);
    }
    i = 0;
    for(const auto& edge : edges_3)
    {
        ASSERT_EQ(edge.distance(), test_3[i++]);
    }
    ASSERT_TRUE(exception_caught);
}

TEST(Graph, 2_Wrong_connection_dimensions_exception)
{
    bool exception_caught {false};
    vector<vector<int>> matrix {
       //  0,  1,  2,  3,  4,  5,  6,  7
        {  0,  3,  2,  5,  0,  0,  0,  0}, //0
        {  3,  0,  0,  0,  3,  0,  0,  0}, //1
        {  2,  0,  0,  0,  1,  6,  0,  0}, //2
        {  5,  0,  0,  2,  0,  0,  0,  0}, //3
        {  3,  0,  1,  0,  0,  0,  4,  0}, //4
        {  0,  0,  0,  0,  0,  4,  2,  0}  //5
    };

    try {
        Graph graph{matrix};
    } catch (std::logic_error) {
        exception_caught = true;
    }
    ASSERT_TRUE(exception_caught);
}
      


TEST(TESTING_IDEA, Ordered_set_verification)
{
    struct lesser 
    {
        bool operator()(const Node* lhs, const Node* rhs) {
            return *lhs < *rhs ;
        }
    };

    vector<vector<int>> matrix {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Graph   graph{matrix};

    Node node_1 = graph.get_node(0);
    node_1.set_tentative_distance(10);
    Node node_2 = graph.get_node(1);
    node_2.set_tentative_distance(15);
    Node node_3 = graph.get_node(2);
    node_3.set_tentative_distance(20);

    
    int i;
    vector<Node*> test_set;

    test_set.push_back(&node_1);
    test_set.push_back(&node_2);
    test_set.push_back(&node_3);
    std::sort(test_set.begin(), test_set.end(), lesser());

    i = 0;
    vector<int> tentative_dist_test {10, 15, 20};
    for(const auto& it : test_set)
    {
        ASSERT_EQ(it->tentative_distance(), tentative_dist_test[i++]);
    }

    node_1.set_tentative_distance(25);
    node_2.set_tentative_distance(15);
    node_3.set_tentative_distance(9);
    std::sort(test_set.begin(), test_set.end(), lesser());

    i = 0;
    tentative_dist_test = {9, 15, 25};
    for(const auto& it : test_set)
    {
        ASSERT_EQ(it->tentative_distance(), tentative_dist_test[i++]);
    }

    test_set.erase(test_set.begin());
    i = 0;
    tentative_dist_test = {15, 25};
    for(const auto& it : test_set)
    {
        ASSERT_EQ(it->tentative_distance(), tentative_dist_test[i++]);
    }

    test_set.erase(test_set.begin());
    Node* it = test_set[0];
    ASSERT_EQ(it->tentative_distance(), 25);
}

TEST(Dijkstra_and_Operations, 1_dijkstra_sets_vector_unvisited_nodes)
{
    vector<vector<int>> matrix {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Graph   graph{matrix};
    int start_id = 0;
    int end_id = 2;
    Dijkstra dijkstra {graph, start_id, end_id};
    
    const vector<int> unvisited {dijkstra.unvisited_nodes()};
    ASSERT_EQ(unvisited.size(), 3);
    ASSERT_EQ(unvisited[0], 0);
    ASSERT_EQ(unvisited[1], 1);
    ASSERT_EQ(unvisited[2], 2);

    ASSERT_EQ(dijkstra.graph_size(), 3);
    Node& node_0 = dijkstra.get_node(0);
    Node node_1 = dijkstra.get_node(1);
    Node node_2 = dijkstra.get_node(2);

    ASSERT_FALSE(node_0.visited());
    ASSERT_FALSE(node_1.visited());
    ASSERT_FALSE(node_2.visited());
}

TEST(Dijkstra_and_Operations, 2_set_start_method)
{
    vector<vector<int>> matrix {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Graph   graph{matrix};
    int start_id = 0;
    int end_id = 2;
    Dijkstra dijkstra {graph, start_id, end_id};
    dijkstra.set_start();
    Node& node_start = dijkstra.get_node(start_id);
    ASSERT_EQ(node_start.tentative_distance(), 0);
    ASSERT_EQ(node_start.parent(), node_start.id());
    ASSERT_EQ(dijkstra.graph_size(), 3);
}

TEST(Dijkstra_and_Operations, 3_mark_as_visited)
{
    vector<vector<int>> matrix {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Graph   graph{matrix};
    int start_id = 0;
    int end_id = 2;
    Dijkstra dijkstra {graph, start_id, end_id};
    
    vector<int> unvisited {dijkstra.unvisited_nodes()};
    ASSERT_EQ(unvisited.size(), 3);
    dijkstra.mark_visited(2);
    unvisited = dijkstra.unvisited_nodes();
    ASSERT_EQ(unvisited.size(), 2);
    dijkstra.mark_visited(1);
    unvisited = dijkstra.unvisited_nodes();
    ASSERT_EQ(unvisited.size(),1);
    dijkstra.mark_visited(0);
    unvisited = dijkstra.unvisited_nodes();
    ASSERT_EQ(unvisited.size(),0);
}

TEST(Dijkstra_and_Operations, 4_next_node_id)
{
    vector<vector<int>> matrix {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Graph   graph{matrix};
    int start_id = 0;
    int end_id = 2;
    Dijkstra dijkstra {graph, start_id, end_id};

    Node& node_0 = dijkstra.get_node(0);
    Node& node_1 = dijkstra.get_node(1);
    Node& node_2 = dijkstra.get_node(2);

    node_0.set_tentative_distance(10);
    node_1.set_tentative_distance(20);
    node_2.set_tentative_distance(30);

    ASSERT_EQ(node_0.tentative_distance(), 10);
    ASSERT_EQ(node_1.tentative_distance(), 20);
    ASSERT_EQ(node_2.tentative_distance(), 30);

    int next_id = dijkstra.next_node_id();
    ASSERT_EQ(next_id, 0);
    dijkstra.mark_visited(next_id);

    next_id = dijkstra.next_node_id();
    ASSERT_EQ(next_id, 1);
    dijkstra.mark_visited(next_id);

    next_id = dijkstra.next_node_id();
    ASSERT_EQ(next_id, 2);
    dijkstra.mark_visited(next_id);
}

TEST(Dijkstra_and_Operations, 5_Trying_real_graph)
{
    stack<int> result;
    result.push(5);
    result.push(4);
    result.push(1);
    result.push(0);

    vector<vector<int>> matrix {
        {0, 10, 20,  0,  0, 0},
        {0,  0,  0, 50, 10, 0},
        {0,  0,  0, 20, 33, 0},
        {0,  0,  0,  0, 20, 2},
        {0,  0,  0,  0,  0, 1},
        {0,  0,  0,  0,  0, 0},
    };
    Graph   graph{matrix};
    int start_id = 0;
    int end_id = 5;
    Dijkstra dijkstra {graph, start_id, end_id};
    stack<int> solution = dijkstra.solve_shortest_path();

    ASSERT_EQ(solution, result);
}

// ---------------------------------
// Main 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

