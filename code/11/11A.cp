#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

long long Dijkstra ( vector<vector<pair<long long, long long>>> const& graph, long long start, long long end){
    long long nodes = graph.size();
    set<pair<long long, long long>> queue;
    vector<long long> weight(nodes, -1);
    
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
    return weight[end];
    }

int main(){
    ios_base::sync_with_stdio(false);

    ifstream input("pathmgep.in");
    ofstream output("pathmgep.out");

    input.tie(nullptr);

    long long nodes, start, end;
    input >> nodes >> start >> end;

    vector<vector<pair<long long, long long>>> graph(nodes);
    for (size_t i = 0; i < nodes; i++) {
        for (size_t j = 0; j < nodes; j++) {
            long long weight;
            input >> weight;
            if (weight != -1 && i != j) {
                graph[i].push_back({j, weight});
            }
        }
    }
    output << Dijkstra(graph, start - 1, end - 1);
    return 0;
}