#include<utility>
#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<queue>
#include "graphClass.h"

using namespace std;


Graph<string> exampleGraph(){
    vector<string> A; 
    A.push_back("A");
    A.push_back("B");
    A.push_back("C");
    
    Graph<string> G(A);

    G.addEdge("A", "B");
    G.addEdge("A", "C");
    G.addEdge("C", "B");

    return G;
}

Graph<string> exampleCycleGraph(){
    vector<string> A;
    A.push_back("A");
    A.push_back("B");
    A.push_back("C");
    A.push_back("D");
    A.push_back("E");

    Graph<string> G(A);

    G.addEdge("A", "B");
    G.addEdge("B", "C");
    G.addEdge("C", "A");
    G.addEdge("C", "D");
    G.addEdge("D", "E");
    G.addEdge("E", "D");

    return G;
}

Graph<string> readGraph(int n){
    vector<string> A;
    cout << "Enter " << n << " nodes." << endl;
    string x;
    for (int i = 0; i < n; i++){
        cin >> x;
        A.push_back(x);
    }
    Graph<string> G(A);
    int nE;
    cout << "Enter number of edges: ";
    cin >> nE;
    for(int i = 0; i < nE; i++){
        string s1, s2;
        cin >> s1 >> s2;
        G.addEdge(s1, s2);
    }
    return G;
}

int main(int argc, char** argv){
    
    Graph<string> G;

    if(argc < 2){
        cout << "Testing default graph." << endl;
        G = exampleGraph();
    }
    else{
        if(string(argv[1]) == "cycle"){
            G = exampleCycleGraph();
        }
        else if(string(argv[1]) == "input"){
            int n = stoi(argv[2]);
            G = readGraph(n);
        }
    }

    cout << "DFS in G" << endl;
    for (int v = 0; v < G.nodes.size(); v++){
        if(!G.inVisited(G.nodes[v]))
            G.Explore(G.nodes[v]);
    }

    cout << "Pre-post in G" << endl;
    for (int i = 0; i < G.nodes.size(); i++){
        cout << G.nodes[i] << ": " << G.pre[G.nodes[i]] << " " << G.post[G.nodes[i]] << endl;
    }

    cout << "BFS in G from first node" << endl;
    G.BreadthFirstSearch(G.nodes[0]);
    for(int i = 0; i < G.AdjacencyList[G.nodes[0]].size(); i++){
        string nxt = G.AdjacencyList[G.nodes[0]][i];
        cout << "Distances between " << G.nodes[0] << "," << nxt << ": " 
                << G.distances[make_pair(G.nodes[0], nxt)] << endl;
    }

    return 0;
}