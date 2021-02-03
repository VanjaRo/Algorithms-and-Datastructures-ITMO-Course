#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

void Degree(vector<vector<int>> const& graph, vector<int>& visited){
    int counter;
    for (int i = 0; i < graph.size(); i++){
        counter = 0;
        for(int route : graph[i]){
            counter ++;
        }
        visited[i] = counter;
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("input.txt");
    ofstream output("output.txt");

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
    Degree(graph, visited);
    for (int i : visited){
        output << i << ' ';
    }

    return 0;
}