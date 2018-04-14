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
    } catch (std::out_of_range) {
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

    vector<int> tentative_dist_test {10, 15, 20};
    
    int i;
    vector<Node*> test_set;
    test_set.push_back(&node_1);
    test_set.push_back(&node_2);
    test_set.push_back(&node_3);
    std::sort(test_set.begin(), test_set.end(), lesser());
    i = 0;
    for(const auto& it : test_set)
    {
        ASSERT_EQ(it->tentative_distance(), tentative_dist_test[i++]);
    }
    tentative_dist_test = {9, 15, 25};
    node_1.set_tentative_distance(25);
    node_2.set_tentative_distance(15);
    node_3.set_tentative_distance(9);
    std::sort(test_set.begin(), test_set.end(), lesser());
    i = 0;
    for(const auto& it : test_set)
    {
        ASSERT_EQ(it->tentative_distance(), tentative_dist_test[i++]);
    }
}

// ---------------------------------
// Main 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

