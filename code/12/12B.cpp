#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


bool Kuhn(const vector<vector<int>>& graph,vector<int>& mm, vector<bool>& used, int from){
    if(used[from])
        return false;
    used[from] = true;
    for (auto to : graph[from]){
        if(mm[to] == -1 || Kuhn(graph, mm, used, mm[to])){
            mm[to] = from;
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("matching.in");
    ofstream output("matching.out");

    input.tie(nullptr);

    int nodes_1, nodes_2, connections;
    input >> nodes_1 >> nodes_2 >> connections;

    vector<vector<int>>graph(nodes_1 + nodes_2);
    for (size_t i = 0; i < connections; i++) {
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
    }

    vector<int> mm(nodes_2, -1);
    vector<bool> used_F(nodes_1);
    for(int from = 0; from < nodes_1; from++){
        for(auto to : graph[from]){
            if(mm[to] == -1){
                mm[to] = from;
                used_F[from] = true;
                break;
            }
        }
    }

    for(int i = 0; i < nodes_1; i++) {
        if (used_F[i])
            continue;
        vector<bool> used(nodes_1);
        Kuhn(graph, mm, used, i);
    }
    int counter = 0;
    for(int i : mm){
        if(i != -1){
            counter ++;
        }
    }
    output << counter;
    return 0;
}
