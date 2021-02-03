#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
const long long INF = 1e9;

struct Edge {
    Edge (int a, int b, long long c): from(a), to(b), cost(c)
    {}
    int from, to;
    long long cost;
};

typedef vector<Edge> China;

vector<int> Ford_Bel ( China const& graph, int start, int nodes){
    
    vector<int> path;

    vector<long long> weight (nodes, INF);
    
    weight[start] = 0;
    vector<int> parents (nodes, -1);
    int lastChanged;
    for (size_t i=0; i<nodes; ++i) {
        lastChanged = -1;
        for (auto edge : graph)
            if (weight[edge.to] > weight[edge.from] + edge.cost) {
                weight[edge.to] = max (-INF, weight[edge.from] + edge.cost);
                parents[edge.to] = edge.from;
                lastChanged = edge.to;
            }
    }

    if (lastChanged != -1){

        for (size_t i=0; i < nodes; ++i)
            lastChanged = parents[lastChanged];

        for (int cur = lastChanged; ; cur = parents[cur]) {
            path.push_back (cur);
            if (cur == lastChanged && path.size() > 1)  break;
        }

        reverse (path.begin(), path.end());
    }
    return path;

}

int main(){
    ios_base::sync_with_stdio(false);

    ifstream input("negcycle.in");
    ofstream output("negcycle.out");

    input.tie(nullptr);

    int nodes;
    input >> nodes;

    China graph;
    for (int from = 0; from < nodes; from++) {
        for (int to = 0; to < nodes; to++) {
            long long weight;
            input >> weight;
            if (weight != 1e9) {
                graph.push_back({from, to, weight});
            }
        }
    }

    vector <int> path = Ford_Bel(graph, 0, nodes);
    if (!path.empty()){
        output << "YES\n";
        output << path.size() << '\n';
        for (auto i : path){
            output << i + 1 << ' ';
        }
    } else {
        output << "NO\n";
    }
    return 0;
}