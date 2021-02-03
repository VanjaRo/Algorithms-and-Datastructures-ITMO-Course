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
void DFS_col(int const& start, vector<vector<int>> const& graph_r, vector<int>& color, int con_ind){
    color[start] = con_ind;
    for(int i = 0; i < graph_r[start].size(); i++) {
        int go_to = graph_r[start][i];
        if (!color[go_to]){
            DFS_col(go_to, graph_r, color, con_ind);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("cond.in");
    ofstream output("cond.out");

    input.tie(nullptr);

    int nodes, connections;

    input >> nodes >> connections;

    vector<vector<int>> graph(nodes);
    vector<vector<int>> graph_r(nodes);

    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph_r[to - 1].push_back(from - 1);
    }
    vector<int> top;
    vector<int> visited(nodes);
    vector<int> color(nodes);
    int con_ind = 1;

    for(int i = 0; i < nodes; i++){
        if(!visited[i]){
            DFS_t(i, graph, visited, top);
        }
    }
    for(int i = 1; i < nodes + 1; i++){
        if(!color[top[nodes - i]]){
            DFS_col(top[nodes - i], graph_r, color, con_ind++);
        }
    }
    output << con_ind - 1 << '\n';
    for(int i = 0; i < nodes; i++){
        output << color[i] << ' ';
    }

    return 0;
}