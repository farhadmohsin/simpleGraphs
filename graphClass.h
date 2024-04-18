#include<utility>
#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

/* helper function
input: vector v, item a
output: returns true if a is in v
*/
template <class NodeType>
bool contains(vector<NodeType> v, NodeType a){
    return (find(v.begin(), v.end(), a) != v.end());
}

/*
Graph class
template implementation so you can
  use this to make a graph with most 
  common item types.
  E.g., Graph<int>, Graph<string> etc.
Comment about the graph structure
  this is a lazily coded up class where client code
  has access to the Graph nodes and edge information directly.
  E.g., for a graph G, client code can directly access G.nodes
  which is a vector of nodes.
*/
template <class NodeType>
class Graph{
protected:
    /* 
    visited will contain nodes that has been visited
      in the current search. Will be cleared before every
      new search.
    */
    vector<NodeType> visited;
    /*
    keeps track of current time, useful for calculating
      pre (starting) and post (ending) times in DFS trees.
    */
    int time;

public:

    /*
    vector of all nodes
    */
    vector<NodeType> nodes;
    /*
    map is a special C++ standard data structure. AdjacencyList
      maps a node to it's list of edges. For example, if 
      edges (a,b) and (a,c) exist, AdjacencyList[a] = vector({b, c}).
    */
    map<NodeType, vector<NodeType> > AdjacencyList;

    /*
    pre, post, and distances will contain information found from
      DFS or BFS searches
    */
    map<NodeType, int> pre;
    map<NodeType, int> post;
    map<pair<NodeType, NodeType>, int> distances;

    // default constructor
    Graph(){time = 0;}
    // constructor that takes in a vector of items as input
    Graph(vector<NodeType> items){
        time = 0;
        addNodes(items);
    }

    // addNodes starts
    /*
    adds all items to the nodes vector and creates empty lists for each node
      in the adjacencyList.
    */
    void addNodes(vector<NodeType> items){
        for(int i = 0; i < items.size(); i++){
            cout << "Adding node: " << items[i] << endl;;
            nodes.push_back(items[i]);
            AdjacencyList.insert(make_pair(items[i], vector<NodeType>()));
        }        
    } //addNodes ends

    // addEdge starts
    /*
      input: edge start and end nodes
      postCondition: add a corresponding entry for end in
        start's adjacencyList
    */
    void addEdge(NodeType start, NodeType end){
        if(contains(nodes, start) && contains(nodes, end)){
            cout << "Inserting edge: " << start << "," << end << endl;
            AdjacencyList[start].push_back(end);
        }
    }

    void Explore(NodeType start){
        cout << "Exploring " << start << endl;
        visited.push_back(start);
        pre[start] = time;
        time++;
        for (int i = 0; i < AdjacencyList[start].size(); i++){
            if(!contains(visited, AdjacencyList[start][i])){
                Explore(AdjacencyList[start][i]);
            }
        }
        post[start] = time;
        time++;
    }

    void DepthFirstSearch(){
        startNewSearch();
        for (int v = 0; v < nodes.size(); v++){
            if(!inVisited(nodes[v]))
                Explore(nodes[v]);
        }
    }

    void BreadthFirstSearch(NodeType start){
        startNewSearch();
        cout << "Starting from node: " << start << endl;
        queue<NodeType> Q;
        Q.push(start);
        distances[make_pair(start, start)] = 0;
        while(!(Q.empty())){
            NodeType top = Q.front();
            Q.pop();
            if(inVisited(top))
                continue;
            visited.push_back(top);
            for(int i = 0; i < AdjacencyList[top].size(); i++){
                NodeType nxt = AdjacencyList[top][i];
                if(!inVisited(nxt)){
                    distances[make_pair(start, nxt)] = distances[make_pair(start, top)] + 1;
                    Q.push(nxt);
                }
            }
        }
    }

    void startNewSearch(){
        time = 0;
        visited.clear();
        pre.clear();
        post.clear();
        distances.clear();
    }

    bool inVisited(NodeType u){
        return contains(visited, u);
    }

    Graph<NodeType> reverseGraph(){
        Graph<NodeType> reverseG;
        reverseG.addNodes(nodes);
        for (int v = 0; v < nodes.size(); v++){
            vector<NodeType> lstv = AdjacencyList[nodes[v]];
            for(int i = 0; i < lstv.size(); i++){
                reverseG.addEdge(lstv[i], nodes[v]);
            }
        }
        return reverseG;
    }
};
