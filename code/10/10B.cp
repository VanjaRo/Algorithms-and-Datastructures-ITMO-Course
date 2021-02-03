#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
#include <vector>

double New_Weight(vector<pair<double, double>> const& graph, vector< double>& weight,
                  vector<int>& start, vector <int>& visited) {
    double min = 1000000;
    int point = -1;
    for (int i : start){
        start.pop_back();
        double x1 = graph[i].first;
        double y1 = graph[i].second;
        for (int j = 1; j < graph.size(); j++) {
            if (!visited[j]) {
                double x2 = graph[j].first;
                double y2 = graph[j].second;
                double weight_t = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
                if (weight_t < weight[j]){
                    weight[j] = weight_t;
                    if (weight_t < min){
                        min = weight_t;
                        point = j;
                    }
                } else if (weight[j] < min){
                    min = weight[j];
                    point = j;
                }
            }
        }
    }

    if (min != 1000000) {
        visited[point] = 1;
        start.push_back(point);
        return min;
    }
    else
        return 0;
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("spantree.in");
    freopen("spantree.out", "w", stdout);

    input.tie(nullptr);

    int nodes;
    input >> nodes;
    vector<pair<double, double>> graph(nodes);
    for (int i = 0; i < nodes; i++){
        double x, y;
        input >> x >> y;
        graph[i] = (make_pair(x, y));
    }
    vector <double> weight(nodes, 1000000);
    vector<int> visited(nodes);
    vector<int> start;
    visited[0] = 1;
    start.push_back(0);
    double tmp = 0;
    for (int i = 1; i < graph.size(); i++){
        double t = New_Weight(graph, weight, start, visited);
        if (t == 0)
            break;
        else
            tmp += t;
    }
    printf("%.3lf", tmp);

    return 0;
}