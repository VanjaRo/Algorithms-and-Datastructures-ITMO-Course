#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

#include <vector>

int DFS(int const& start, vector<vector<int>> const& graph, vector<int>& visited, vector<int>& top){
    visited[start] = 1;
    for(int i = 0; i < graph[start].size(); i++){
        int go_to = graph[start][i];
        if (visited[go_to] == 1){
            return -1;
        } else if (!visited[go_to]){
            int tmp = DFS(go_to, graph, visited, top);
            if (tmp == -1){
                return -1;
            }
        }
    }
    visited[start] = 2;
    top.push_back(start);
}


int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("topsort.in");
    ofstream output("topsort.out");

    input.tie(nullptr);

    int nodes, connections;

    input >> nodes >> connections;
    vector<vector<int>> graph(nodes);
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    vector<int> top;
    vector<int> visited(nodes);

    for(int i = 0; i < nodes; i++){
        if(!visited[i]){
            int tmp = DFS(i, graph, visited, top);
            if(tmp == -1){
                output << -1;
                return 0;
            }
        }
    }
    while (!top.empty()){
        output << top.back() + 1 << ' ';
        top.pop_back();
    }

    return 0;
}