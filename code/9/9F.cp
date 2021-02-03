#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

enum {
    GRAY = 1,
    BLACK = 2
};


void DFS(int const& start, vector<vector<int>> const& graph, vector<int>& visited, vector<int>& win){
    vector<int> stack;
    stack.push_back(start);
    int win_vert = 0;
    while(!stack.empty()){
        int go_to = stack.back();

        if (visited[go_to] == GRAY){
            win_vert = 0;
            for (int i : graph[go_to]){
                if (!win[i]){
                    win_vert = 1;
                }
            }
            win[go_to] = win_vert;
            visited[go_to] = BLACK;
            stack.pop_back();
            continue;
        } else if (visited[go_to] == BLACK){
            stack.pop_back();
            continue;
        }
        visited[go_to] = GRAY;
        for (int i : graph[go_to]){
            if(!visited[i]){
                stack.push_back(i);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("game.in");
    ofstream output("game.out");

    input.tie(nullptr);

    int nodes, connections, start;

    input >> nodes >> connections >> start;
    vector<vector<int>> graph(nodes);
    for (int i = 0; i < connections; i++){
        int from, to;
        input >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    vector<int> visited(nodes);
    vector<int> win_p(nodes);

    DFS(start - 1, graph, visited, win_p);

    output << (win_p[start - 1] == 1 ? "First player wins": "Second player wins");
    return 0;
}