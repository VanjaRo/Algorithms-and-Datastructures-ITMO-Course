#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


int main(){
    ios_base::sync_with_stdio(false);

    ifstream input("pathsg.in");
    ofstream output("pathsg.out");

    input.tie(nullptr);

    long long nodes, connections;
    input >> nodes >> connections;

    vector<vector< long long>> graph(nodes, vector<long long>(nodes, 100001));
    for (size_t i = 0; i < connections; i++) {
            long long from_, to_;
            input >> from_ >> to_ >> graph[from_ - 1][to_ - 1];
    }
    for (size_t i = 0; i < nodes; i++){
        graph[i][i] = 0;
    }
    for (size_t i = 0; i < nodes; i++) {
        for (size_t j = 0; j < nodes; j++) {
            for (size_t k = 0; k < nodes; k++){
                graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
            }
        }
    }

    for (size_t i = 0; i < nodes; i++){
        for(size_t j = 0; j < nodes; j++){
            output << graph[i][j] << ' ';
        }
        output << '\n';
    }
    return 0;
}