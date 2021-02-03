#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

#include <vector>

void DFS(vector<vector<int>> &graph, int index, vector<int>  &visited, int &con_ind){
    queue<int>  q;
    q.push(index);
    while (!q.empty()) {
        int go_to = q.front();
        q.pop();
        for (int i = 0;  i < graph[go_to].size(); i++){
            if (visited[graph[go_to][i]] == 0)
                q.push(graph[go_to][i]);
        }
        visited[go_to] = con_ind;
    }
    con_ind++;
}


int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("components.in");
    ofstream output("components.out");
    input.tie(nullptr);

    int nodes, connections;

    vector<vector<int>> graph;
    input >> nodes >> connections;
    graph.resize(nodes);

    vector<int>  visited;
    visited.resize(nodes);

    int con_ind = 1;
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);

    }
    for (int i = 0; i < nodes; i++){
        if (visited[i] == 0)
            DFS(graph, i, visited, con_ind);
    }
    output << con_ind - 1<< '\n';
    for (int i = 0; i < nodes; i++){
        output << visited[i] << ' ';
    }

    return 0;
}