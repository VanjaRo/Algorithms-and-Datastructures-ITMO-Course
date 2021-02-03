#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge{
    int to;
    int flow;
    int cap;
    int Ind;
    int revInd;
};
using namespace std;

vector<int> levels;
vector<vector<int>> path;
vector<vector<Edge>> adj;
vector<int> counter;
int vertAmount;
int edgAmount;
int s;
int t;


bool BFS(int s_, int t){
    levels.assign(vertAmount, 0);
    levels[s_] = 1;
    queue<int> q;
    q.push(s_);
    while(!q.empty() && !levels[t]){
        int from = q.front();
        q.pop();
        for(auto& edge : adj[from]){
            if (!levels[edge.to] && edge.flow < edge.cap){
                levels[edge.to] = levels[from] + 1;
                q.push(edge.to);
            }
        }
    }
    return levels[t];
}
int dfsFlow(int current, int flow){
    if(!flow)
        return 0;
    if(current == t)
        return flow;
    for(;counter[current] < adj[current].size(); counter[current] ++){
        Edge& edge = adj[current][counter[current]];
        if(levels[edge.to] == levels[current] + 1 && edge.flow < edge.cap){
            int curFlow = dfsFlow(edge.to, min(flow, edge.cap - edge.flow));
            if (curFlow){
                edge.flow += curFlow;
                adj[edge.to][edge.revInd].flow -= curFlow;
                return curFlow;
            }
        }
    }
    return 0;
}
int decompose(int vert, int minFlow){
    if (vert == t) {
        path.emplace_back();
        return minFlow;
    }
    for (auto& edge : adj[vert]){
        if (edge.flow > 0){
            int flow  = decompose(edge.to, min(minFlow, edge.flow));
            if (flow){
                path.back().emplace_back(edge.Ind);
                if (vert == s){
                    path.back().push_back(path[path.size() - 1].size());
                    path.back().push_back(flow);
                    reverse(path.back().begin(), path.back().end());
                }
                edge.flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}
int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("decomposition.in");
    ofstream output("decomposition.out");

    input.tie(nullptr);

    input >> vertAmount >> edgAmount;
    adj.resize(vertAmount);
    counter.resize(vertAmount,0);
    for(int i = 0; i < edgAmount; i++) {
        int from, to, cap;
        input >> from >> to >> cap;
        Edge a {to - 1, 0, cap, i + 1, int(adj[to - 1].size())};
        Edge b {from - 1, 0, 0, i + 1, int(adj[from - 1].size())};
        adj[from - 1].push_back(a);
        adj[to - 1].push_back(b);
    }
    s = 0;
    t = vertAmount - 1;
    while(BFS(s, t)){
        while (dfsFlow(s, INT_MAX));
        counter.assign(vertAmount, 0);
    }
    while(decompose(s, INT_MAX));
    output << path.size() << '\n';
    for(auto i : path){
        for(auto j : i){
            output << j << ' ';
        }
        output << '\n';
    }
    return 0;
}