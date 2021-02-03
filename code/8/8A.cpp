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
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from-1].push_back(to);
    }
    for (int i = 0; i < nodes; i++){
        for (int j = 0; j < nodes; j++){
            int checker = 0;
            for(int d = 0; d < graph[i].size(); d++){
                if (graph[i][d] == j+1){
                    output << "1 ";
                    checker ++;
                    break;
                }
            }
            if (!checker)
                output << "0 ";
        }
        output << '\n';
    }
    return 0;
}