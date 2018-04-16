#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <limits>
#include <stack>
#include <stdexcept>
#include <string>
using std::vector;
using std::set;
using std::priority_queue;
using std::numeric_limits;
using std::stack;

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
        Node(int id, vector<int> node_distances={})
            : mId{id}
            , mTentativeDistance{std::numeric_limits<int>::max()}
            , mVisited{false}
            , mParent{std::numeric_limits<int>::max()}
        {
            int toNode = 0;
            for(const auto& distance : node_distances)
            {
                mEdges.push_back({mId, toNode++, distance});
            }
            std::sort(mEdges.begin(), mEdges.end(), greater());
        }

        Node& operator= (const Node& rhs)
        {
            if( &rhs != this)
            {
                mId = rhs.mId;
                mTentativeDistance = rhs.mTentativeDistance;
                mVisited = rhs.mVisited;
                mEdges = rhs.mEdges;
                mParent = rhs.mParent;
            }
            return *this;
        }

        // Getters
        virtual int id(void) const {return mId;}
        virtual int tentative_distance(void) const {return mTentativeDistance;}
        virtual int parent(void) const {return mParent;}
        virtual vector<Edge> all_edges(void) const {return mEdges;}
        virtual bool visited(void) const {return mVisited;}

        // Setters
        virtual void set_tentative_distance(int dist){mTentativeDistance = dist;}
        virtual void set_unvisited(void){mVisited = false;}
        virtual void set_visited(void){mVisited = true;}
        virtual void set_parent(int parent){mParent = parent;}

        friend bool operator< (const Node& lhs, const Node& rhs) {
            return lhs.mTentativeDistance < rhs.mTentativeDistance;
        }

        friend bool operator> (const Node& lhs, const Node& rhs) {
            return lhs.mTentativeDistance > rhs.mTentativeDistance;
        }

private:
        int          mId;
        int          mTentativeDistance;
        bool         mVisited;
        vector<Edge> mEdges;
        int          mParent;
};

class Graph
{
    typedef vector<vector<int>> connection_matrix_t;
    public:
        Graph(connection_matrix_t connection_matrix)
        {
            if(connection_matrix.size() != connection_matrix[0].size())
            {
                throw std::logic_error("wrong connection matrix dimmensions");
            }

            int id = 0;
            for(const auto& line : connection_matrix)
            {
                mNodes.push_back({id++, line});
            }
        }

        // Getter
        virtual Node& get_node(int id) {
            try {
                return mNodes.at(id);
            } catch(std::out_of_range)
            {
                std::string msg = "Node '" + std::to_string(id) + "' NOT in graph";
                throw std::logic_error(msg);
            }
        }
        virtual size_t size(void) const {return mNodes.size();}

    private:
        vector<Node> mNodes;
};

class Dijkstra
{
    struct lesser 
    {
        bool operator()(const Node* lhs, const Node* rhs) {
            return *lhs < *rhs ;
        }
    };

    public:
        Dijkstra(Graph& graph, int start_node_id, int end_node_id)
            : mGraph{graph}, mStartId{start_node_id}, mEndId{end_node_id}
        {
           mark_all_nodes_unvisited(); 
        }

        virtual stack<int> solve_shortest_path() 
        {
           set_start();
           int current_node_id = mStartId;
           while(!finished())
           {
               update_neighbours(current_node_id);
               mark_visited(current_node_id);
               current_node_id = next_node_id();
           }
           return get_solution();
        }

        virtual void set_start(void)
        {
            Node& start = mGraph.get_node(mStartId);
            start.set_tentative_distance(0);
            start.set_parent(mStartId);
        }

        virtual void update_neighbours(int id) 
        {
            Node& node = mGraph.get_node(id);
            vector<Edge> edges = node.all_edges();
            for(const auto& edge : edges)
            {
                Node& neighbour = mGraph.get_node(edge.toNode());
                if(!neighbour.visited() && edge.distance())
                {
                    int tentative = node.tentative_distance() + edge.distance();
                    if(tentative < neighbour.tentative_distance())
                    {
                        neighbour.set_tentative_distance(tentative);
                        neighbour.set_parent(id);
                    }
                }
            }
        }

        virtual void mark_visited(int id) 
        {
            mGraph.get_node(id).set_visited();
            mUnvisited.erase(mUnvisited.begin());
        }

        virtual int next_node_id(void) 
        {
            int node_id = -1;
            std::sort(mUnvisited.begin(), mUnvisited.end(), lesser());
            if(!mUnvisited.empty())
            {
                node_id = mUnvisited[0]->id();
            }
            return node_id;
        }

        virtual bool finished(void)
        {
            static Node& ending = mGraph.get_node(mEndId);
            if(ending.visited())
            {
                return true;
            }
            if(mUnvisited[0]->tentative_distance() == numeric_limits<int>::max())
            {
                return true;
            }
            return false;
        }

        virtual stack<int> get_solution(void)
        {
            stack<int>    sol;
            Node& node = mGraph.get_node(mEndId);
            if(node.parent() == std::numeric_limits<int>::max())
            {
                // Ending node not reached -> solution: no path
                // between 'start' and 'end'
                return sol;
            }
            while(node.id() != mStartId)
            {
                sol.push(node.id());
                node = mGraph.get_node(node.parent());
            }
            sol.push(mStartId);
            return sol;
        }

        virtual Node& get_node(int id) const { return mGraph.get_node(id);}
        virtual const vector<int> unvisited_nodes(void) const {
            vector<int> unvisited;
            for(const auto& node : mUnvisited)
            {
                unvisited.push_back(node->id());
            }
            return unvisited;
        }

        virtual size_t graph_size(void){return mGraph.size();}

    protected:
        virtual void mark_all_nodes_unvisited(void)
        {
            size_t sz = mGraph.size();
            for(unsigned i = 0 ; i < sz ; i++)
            {
                Node& node{mGraph.get_node(i)};
                mUnvisited.push_back(&node);
                node.set_unvisited();
            }
            std::sort(mUnvisited.begin(), mUnvisited.end(), lesser());
        }

    private:
        Graph&        mGraph;
        int           mStartId;
        int           mEndId;
        vector<Node*> mUnvisited;
};

