#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <stack>
#include<algorithm>

typedef vector<vector<pair<long long, long long>>> China;

void DFS_t_h (long long const& start, China const& graph, vector<bool>& visited, vector<long long >& top){
    visited[start] = true;
    for(auto tmp : graph[start]){
        if (!visited[tmp.first]){
            DFS_t_h(tmp.first, graph, visited, top);
        }
    }
    top.push_back(start);
}

void DFS_t_m(China const& graph, vector<long long >& top){
    long long nodes = graph.size();
    vector<bool> visited(nodes);
    for (long long i = 0; i < nodes; i++){
        if(!visited[i]){
            DFS_t_h(i, graph, visited, top);
        }
    }
}

void DFS_col(long long const& start, China const& graph_r, vector<long long>& color, long long con_ind){
    color[start] = con_ind;
    for (auto& tmp : graph_r[start]) {
        if (color[tmp.first] == -1) {
            DFS_col(tmp.first, graph_r, color, con_ind);
        }
    }
}

void DFS(long long const& start, China const& graph, vector<bool>& visited){
    visited[start] = true;
    for (auto tmp : graph[start])
        if (!visited[tmp.first])
            DFS(tmp.first, graph, visited);
}

bool Reacheable(long long const root, China const& graph){
    long long nodes = graph.size();
    vector<bool> visited_tmp (nodes);
    DFS(root, graph, visited_tmp);
    for (auto v : visited_tmp){
        if (!v){
            return false;
        }
    }
    return true;
}
long long Condensation(China const& graph, vector<long long>& comp){
    long long nodes = graph.size();
    vector<long long> top(nodes);
    DFS_t_m(graph, top);

    China graph_r(nodes);

    for (long long i = 0; i < nodes; i++){
        for (auto tmp : graph[i])
            graph_r[tmp.first].push_back({i, tmp.second});
    }
    long long numComp = 0;
    reverse(top.begin(), top.end());
    for(long long i = 0; i < nodes; i++){
        if(comp[top[i]] == -1){
            DFS_col(top[i], graph_r, comp, numComp++);
        }
    }
    return numComp;
}
long long COVID_19(China const& graph, long long root){
    long long min_ST = 0;
    long long nodes = graph.size();
    vector<long long> min_Edges (nodes, 10000000000000000);

    for (long long i = 0; i < nodes; i++){
        for (auto tmp : graph[i]){
            min_Edges[tmp.first] = tmp.second < min_Edges[tmp.first] ? tmp.second:min_Edges[tmp.first];
        }
    }
    for (long long i = 0; i < nodes; i++){
        if (i != root){
            min_ST += min_Edges[i];
        }
    }
    China zero_Edges(nodes);
    for (long long i = 0; i < nodes; i++){
        for (auto tmp : graph[i]){
            if(tmp.second == min_Edges[tmp.first])
                zero_Edges[i].push_back({tmp.first, 0});
        }
    }
    if (Reacheable(root, zero_Edges)) {
            return min_ST;
    }
    vector<long long> comp (nodes, -1);
    long long maxComp_ = Condensation(zero_Edges, comp);
    China reforged (maxComp_);
    for (long long i = 0; i < nodes; i++){
        for (auto tmp : graph[i]){
            if(comp[i] != comp[tmp.first])
                reforged[comp[i]].push_back({comp[tmp.first],
                        tmp.second - min_Edges[tmp.first]});
        }
    }

    return  min_ST + COVID_19(reforged, comp[root]);
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("chinese.in");
    ofstream output("chinese.out");

    input.tie(nullptr);

    long long nodes, connections;
    input >> nodes >> connections;

    China graph(nodes);

    for (long long i = 0; i < connections; i++){
        long long from, to, weight;
        input >> from >> to >> weight;
        graph[from-1].push_back({to-1, weight});
    }
    if (Reacheable(0, graph)){
        output << "YES\n";
        output << COVID_19(graph, 0);
    } else
        output << "NO";
    return 0;
}