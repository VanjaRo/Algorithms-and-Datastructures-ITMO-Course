#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge{
    int to;
    int flow;
    int cap;
    int revInd;
};
using namespace std;

vector<int> levels;
vector<vector<int>> path;
vector<vector<Edge>> adj;
vector<int> counter;
vector<pair<int, int>> order;
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

void addEdg(int from, int to, int cap, bool trigger = false){
    Edge a {to, 0, cap, int(adj[to].size())};
    Edge b {from, 0, 0, int(adj[from].size())};
    adj[from].push_back(a);
    adj[to].push_back(b);
    if(trigger)
        order.emplace_back(from, adj[from].size() - 1);
}
int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("circulation.in");
    ofstream output("circulation.out");

    input.tie(nullptr);

    input >> vertAmount >> edgAmount;
    vertAmount += 2;

    adj.resize(vertAmount);
    counter.resize(vertAmount,0);

    s = 0;
    t = vertAmount - 1;
    for(int i = 0; i < edgAmount; i++) {
        int from, to, minF, maxF;
        input >> from >> to >> minF >> maxF;
        addEdg(s, to , minF);
        addEdg(from, to, maxF - minF, true);
        addEdg(from, t, minF, true);
    }
    while(BFS(s, t)){
        while (dfsFlow(s, INT_MAX));
        counter.assign(vertAmount, 0);
    }

    for (auto edge : adj[0]){
        if (edge.flow < edge.cap){
            output << "NO";
            return 0;
        }
    }
    output << "YES\n";
    for (int i = 0; i < order.size(); i += 2)
        output << adj[order[i].first][order[i].second].flow + adj[order[i + 1].first][order[i + 1].second].flow << '\n';
    return 0;
}