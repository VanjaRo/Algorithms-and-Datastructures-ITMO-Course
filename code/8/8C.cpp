#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#include <vector>

void sum_of_minimums(const vector<vector<int>> &numbers)
{

}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    int nodes, connections;
    vector<vector<int>> graph;
    input >> nodes >> connections;
    graph.resize(nodes);
    for (int i = 0; i < nodes; i++){
        graph[i].resize(nodes);
    }
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        if (!graph[from - 1][to - 1]){
            graph[from - 1][to - 1] = 1;
            graph[to - 1][from - 1] = 1;
        } else {
            output << "YES";
            return 0;
        }
    }
    output << "NO";
    return 0;
}