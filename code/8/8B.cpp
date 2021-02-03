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
    int nodes;
    vector<vector<int>> graph;
    input >> nodes;
    graph.resize(nodes);
    for (int i = 0; i < nodes; i++){
        graph[i].resize(nodes);
    }
    for (int i = 0; i < nodes; i++){
        for (int j = 0; j < nodes; j++){
            int tmp;
            input >> tmp;
            if (tmp)
                graph[i][j] = 1;
            else
                graph[i][j] = 0;
        }
    }
    for (int i = 0; i < nodes; i++){
        for (int j = 0; j < nodes; j++){
            if (graph[i][j] != graph[j][i]){
                output << "NO";
                return 0;
            }
            if(i == j){
                if(graph[i][j]) {
                    output << "NO";
                    return 0;
                }
            }

        }
    }
    output << "YES";
    return 0;
}