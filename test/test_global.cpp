#include <gtest/gtest.h>
#include "elements.hpp"
#include <queue>

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

// ---------------------------------
// Main - 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

