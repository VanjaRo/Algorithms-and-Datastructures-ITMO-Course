#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <set>


int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("spantree3.in");
    ofstream output("spantree3.out");

    input.tie(nullptr);

    long long nodes,  connections;
    input >> nodes >> connections;
    vector<vector<pair<long long, long long>>> graph(nodes);
    for (long long i = 0; i < connections; i++){
        long long from, to, weight;
        input >> from >> to >> weight;
        graph[from-1].push_back((make_pair(to-1, weight)));
        graph[to-1].push_back((make_pair(from-1, weight)));
    }
    vector<long long> inside(nodes, 0);
    set <pair<long long,long long>> set;
    set.insert(make_pair(0, 0));
    long long mst = 0;
    while(!set.empty()){
        long long to = set.begin()->second;
        long long dist = set.begin()->first;
        set.erase(set.begin());
        if (inside[to])
            continue;
        inside[to] = 1;
        mst += dist;
        for (pair <long long, long long> j : graph[to]){
            long long dir = j.first;
            if (!inside[dir]){
                long long len = j.second;
                set.insert(make_pair(len, dir));
            }
        }
    }
    output << mst;




    return 0;
}