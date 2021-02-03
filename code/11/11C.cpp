#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

typedef vector<vector<pair<long long, long long>>> China;

void Dijkstra ( China const& graph, long long start, vector<long long> & weight){
    set<pair<long long, long long>> queue;
    weight[start] = 0;
    queue.insert({0, start});

    while (!queue.empty()){
        long long index_to = queue.begin()->second;
        long long path_w = queue.begin()-> first;
        queue.erase(queue.begin());
        for (auto edge : graph[index_to]) {
            if (weight[edge.first] > edge.second + path_w || weight[edge.first] == -1) {
                queue.erase({weight[edge.first], edge.first});
                weight[edge.first] = edge.second + path_w;
                queue.insert({edge.second + path_w, edge.first});
            }

        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);

    ifstream input("pathbgep.in");
    ofstream output("pathbgep.out");

    input.tie(nullptr);

    long long nodes, connections;
    input >> nodes >> connections;

    China graph(nodes);
    for (size_t i = 0; i < connections; i++) {
        long long from, to, weight;

        input >> from >> to >> weight;
        graph[from - 1].push_back({to - 1, weight});
        graph[to - 1].push_back({from - 1, weight});
    }
    vector<long long> weights(nodes, -1);

    Dijkstra(graph,  0, weights);

    for (auto edge : weights){
        output << edge << ' ';
    }
    return 0;
}