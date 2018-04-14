#include <gtest/gtest.h>
#include "elements.hpp"
#include <queue>
#include <vector>

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
    std::vector<int> distances {1,2,3,4,5};
    Node node {0, distances };

    std::vector<Edge> edges = node.all_edges();

    int i = 0;
    for(const auto& edge : edges)
    {
        ASSERT_EQ(edge.distance(), distances[i++]);
    }
}

TEST(Node, 2_Node_s_edges_in_order_2)
{
    std::vector<int> distances {5,4,3,2,1};
    std::vector<int> test_order {1,2,3,4,5};

    Node node {0, distances };
    std::vector<Edge> edges = node.all_edges();

    int i = 0;
    for(const auto& edge : edges)
    {
        ASSERT_EQ(edge.distance(), test_order[i++]);
    }
}

TEST(Node, 3_copy_const)
{
    std::vector<int> distances {5,4,3,2,1};
    std::vector<int> test_order {1,2,3,4,5};
    Node orig_node {0, distances };
    Node node {orig_node};
    std::vector<Edge> edges = node.all_edges();

    int i = 0;
    for(const auto& edge : edges)
    {
        ASSERT_EQ(edge.distance(), test_order[i++]);
    }
}

TEST(Graph, 1_Grap_creation)
{
    std::vector<std::vector<int>> matrix {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    bool exception_caught {false};
    Graph   graph{matrix};
    Node node_1 = graph.get_node(0);
    std::vector<Edge> edges_1 = node_1.all_edges();
    std::vector<int> test_1 = {1,2,3};
    Node node_2 = graph.get_node(1);
    std::vector<Edge> edges_2 = node_2.all_edges();
    std::vector<int> test_2 = {4,5,6};
    Node node_3 = graph.get_node(2);
    std::vector<Edge> edges_3 = node_3.all_edges();
    std::vector<int> test_3 = {7,8,9};

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

// ---------------------------------
// Main 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

