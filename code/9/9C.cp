#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

#include <vector>

int BFS(vector<vector<int>> &graph, int index, vector<int>  &visited){
    queue<int>  q;
    q.push(index);
    visited[index] = 1;
    while (!q.empty()) {
        int go_to = q.front();
        q.pop();
        for (int i = 0;  i < graph[go_to].size(); i++){
            if (visited[graph[go_to][i]] == 0 && visited[go_to] == 1){
                visited[graph[go_to][i]] = 2;
                q.push(graph[go_to][i]);
            }
            else if (visited[graph[go_to][i]] == 0 && visited[go_to] == 2){
                visited[graph[go_to][i]] = 1;
                q.push(graph[go_to][i]);
            }
            else if (visited[graph[go_to][i]] == visited[go_to]){
                return -1;
            }
        }

    }
    return 0;
}



int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("bipartite.in");
    ofstream output("bipartite.out");

    input.tie(nullptr);

    int nodes, connections;

    input >> nodes >> connections;
    vector<vector<int>> graph(nodes);
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }
    vector<int> visited(nodes);
    int ERROR = 0;
    for (int i = 0; i < nodes; i++)
        if(!visited[i] && BFS(graph, i, visited)) {
            ERROR = 1;
        }
    if (ERROR) {
        output << "NO";
    } else
        output << "YES";
    return 0;
}