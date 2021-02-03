#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

#include <vector>

int DFS(int const& start, vector<vector<int>> const& graph, vector<int>& visited, queue<int>& cycle){
    if(!visited[start])
        visited[start] = 1;
    for(int i = 0; i < graph[start].size(); i++){
        int go_to = graph[start][i];
        if (visited[go_to] == 1){
            cycle.push(go_to);
            visited[go_to] = 3;
            DFS(go_to, graph, visited, cycle);
            return 3;
        } else if (visited[go_to] == 3){
            return 3;
        } else if (!visited[go_to]){
            int tmp = DFS(go_to, graph, visited, cycle);
            if (tmp == 3 & visited[start] == 3){
                return 3;
            } else if (tmp == 3 & visited[start] == 1) {
                visited[start] = 2;
                return 3;
            }
        }
    }
    visited[start] = 2;
    return 1;
}


int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("cycle.in");
    ofstream output("cycle.out");

    input.tie(nullptr);

    int nodes, connections;

    input >> nodes >> connections;
    vector<vector<int>> graph(nodes);
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    queue<int> cycle;
    vector<int> visited(nodes);

    for(int i = 0; i < nodes; i++){
        if(!visited[i]){
            int tmp = DFS(i, graph, visited, cycle);
            if(tmp == 3){
                output << "YES" << '\n';
                while (!cycle.empty()){
                    output << cycle.front() + 1<< ' ';
                    cycle.pop();
                }
                return 0;
            }
        }
    }
    output << "NO";

    return 0;
}