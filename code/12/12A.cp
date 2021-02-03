#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//typedef vector<vector<pair<int, int>>> listEdges;

bool BFS(const vector<vector<long long>>& rGraph, int source, int sink, vector<int>& parent){
    vector<bool> visited(rGraph.size());
    queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    while(!q.empty()){
        int from = q.front();
        q.pop();
        for(int to = 0; to < rGraph.size(); to++){
            if(!visited[to] && rGraph[from][to]){
                q.push(to);
                parent[to] = from;
                visited[to] = true;
            }
        }
    }
    return visited[sink];
}
long long fordFulkerson(const vector<vector<long long>>& Graph, int source, int sink){
    vector<vector<long long>> rGraph(Graph);
    vector<int> parent(Graph.size());
    long long maxFlow = 0;

    while(BFS(rGraph, source, sink, parent)){
        long long path_flow = INTMAX_MAX;
        int to = sink;
        while(to != source){
            int from = parent[to];
            path_flow = min(path_flow, rGraph[from][to]);
            to = from;
        }
        to = sink;
        while(to != source){
            int from = parent [to];
            rGraph[from][to] -= path_flow;
            rGraph[to][from] += path_flow;
            to = from;
        }
        maxFlow += path_flow;
    }
    return maxFlow;
}
int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("maxflow.in");
    ofstream output("maxflow.out");

    input.tie(nullptr);

    int nodes, connections;
    input >> nodes >> connections;

    vector<vector<long long>>Graph(nodes, vector<long long>(nodes));
    for (size_t i = 0; i < connections; i++) {
        int from, to, passes;
        input >> from >> to >> passes;
        Graph[from - 1][to - 1] = passes;
    }
    output << fordFulkerson(Graph, 0, nodes - 1);
    return 0;
}