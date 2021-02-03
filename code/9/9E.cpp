#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

#include <vector>

void DFS_t(int const& start, vector<vector<int>> const& graph, vector<int>& visited, vector<int>& top){
    visited[start] = 1;
    for(int i = 0; i < graph[start].size(); i++){
        int go_to = graph[start][i];
        if (!visited[go_to]){
            DFS_t(go_to, graph, visited, top);
        }
    }
    top.push_back(start);
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("hamiltonian.in");
    ofstream output("hamiltonian.out");

    input.tie(nullptr);

    int nodes, connections;

    input >> nodes >> connections;
    vector<vector<int>> graph(nodes);
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    vector<int> visited(nodes);
    int NICE = 0;
    vector<int> top;

    for (int i = 0; i < nodes; i++)
        if(!visited[i]) {
            DFS_t(i, graph, visited, top);
        }
    for (int i = top.size()-1; i > 0; i--) {
        for(int j : graph[top[i]]){
            if (top[i - 1] == j) {
                NICE = 1;
                break;
            }
        }
        if (NICE == 0){
            output << "NO";
            return 0;
        }
        NICE = 0;
    }

    output << "YES";
    return 0;
}