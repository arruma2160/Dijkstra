#include <queue>

class Edge 
{
    public:
        Edge(int fromNode, int toNode, int distance)
            :mFromNode{fromNode}, mToNode{toNode}, mDistance{distance} 
        {}
        
        virtual int fromNode(void){return mFromNode;}
        virtual int toNode(void){return mToNode;}
        virtual int distance(void){return mDistance;}

        virtual void set_distance(int distance){mDistance = distance;}

        friend bool operator< (const Edge& lhs, const Edge& rhs) {
            // Definition of less than relation between two edges:
            // Edge1 < Edge2 if Edge1.distance > Edge2.distance
            return lhs.mDistance > rhs.mDistance;
        }

    private:
        int mFromNode;
        int mToNode;
        int mDistance;
};

