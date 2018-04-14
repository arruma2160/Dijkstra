#include <vector>
#include <algorithm>
using std::vector;

class Edge 
{
    public:
        Edge(int fromNode, int toNode, int distance)
            :mFromNode{fromNode}, mToNode{toNode}, mDistance{distance} 
        {}
        
        // Getters
        virtual int fromNode(void) const {return mFromNode;}
        virtual int toNode(void) const {return mToNode;}
        virtual int distance(void) const {return mDistance;}

        // Setters
        virtual void set_distance(int distance){mDistance = distance;}
        virtual void set_from_node(int fromNode) = delete;
        virtual void set_to_node(int toNode) = delete;

        friend bool operator< (const Edge& lhs, const Edge& rhs) {
            // Definition of less than relation between two edges:
            // Priority => Edge1 < Edge2 if Edge1.distance > Edge2.distance
            return lhs.mDistance > rhs.mDistance;
        }

        friend bool operator> (const Edge& lhs, const Edge& rhs) {
            return lhs.mDistance < rhs.mDistance;
        }

    private:
        int mFromNode;
        int mToNode;
        int mDistance;
};


class Node
{
    struct greater 
    {
        bool operator()(const Edge& lhs, const Edge& rhs) {
            return lhs > rhs ;
        }
    };
    public:
        Node(int id, vector<int> all_edges_distances)
            : mId{id}, mTentativeDistance{std::numeric_limits<int>::max()}
        {
            int toNode = 0;
            for(const auto& distance : all_edges_distances)
            {
                mEdges.push_back({mId, toNode++, distance});
            }
            std::sort(mEdges.begin(), mEdges.end(), greater());
        }

        // Getters
        virtual int id(void){return mId;}
        virtual int tentative_distance(void){return mTentativeDistance;}
        virtual vector<Edge> all_edges(void){return mEdges;}

        // Setters
        virtual void set_tentative_distance(int dist){mTentativeDistance = dist;}

    private:
        const int mId;
        int mTentativeDistance;

        vector<Edge> mEdges;
};

