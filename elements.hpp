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
        Node(int id, vector<int> node_distances)
            : mId{id}
            , mTentativeDistance{std::numeric_limits<int>::max()}
            , mVisited{false}
        {
            int toNode = 0;
            for(const auto& distance : node_distances)
            {
                mEdges.push_back({mId, toNode++, distance});
            }
            std::sort(mEdges.begin(), mEdges.end(), greater());
        }

        // Getters
        virtual int id(void){return mId;}
        virtual int tentative_distance(void){return mTentativeDistance;}
        virtual vector<Edge> all_edges(void){return mEdges;}
        virtual bool has_been_visited(void){return mVisited;}

        // Setters
        virtual void set_tentative_distance(int dist){mTentativeDistance = dist;}
        virtual void set_visited(void){mVisited = true;}

    private:
        const int    mId;
        int          mTentativeDistance;
        bool         mVisited;
        vector<Edge> mEdges;
};

class Graph
{
    typedef vector<vector<int>> connection_matrix_t;
    public:
        Graph(connection_matrix_t connection_matrix)
        {
            int id = 0;
            for(const auto& line : connection_matrix)
            {
                mNodes.push_back({id++, line});
            }
        }

        // Getter
        virtual Node& get_node(int id){return mNodes.at(id);}

    private:
        vector<Node> mNodes;
};

