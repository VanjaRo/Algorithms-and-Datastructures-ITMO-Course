#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

#include <vector>

void BFS(vector<vector<int>> &graph, pair<int, int>& st_index, pair<int, int>& end_index, vector<int>  &visited){
    queue<pair<int, int>>  q;
    q.push(st_index);
    while (!q.empty()) {
        pair<int, int> go_to = q.front();
        q.pop();
        pair<int, int> tmp;

        //L
        tmp = make_pair(go_to.first, go_to.second -1);
        if ( graph[go_to.first][go_to.second - 1] != -1 && visited[graph[go_to.first][go_to.second - 1]] == 0
        && tmp != st_index) {
            q.push(tmp);
            visited[graph[go_to.first][go_to.second - 1]] = visited[graph[go_to.first][go_to.second]] + 1;
        }
        //D
        tmp = make_pair(go_to.first + 1, go_to.second);
        if ( graph[go_to.first + 1][go_to.second] != -1 && visited[graph[go_to.first + 1][go_to.second]] == 0
             && tmp != st_index) {
            q.push(tmp);
            visited[graph[go_to.first + 1][go_to.second]] = visited[graph[go_to.first][go_to.second]] + 1;
        }
        //U
        tmp = make_pair(go_to.first - 1, go_to.second);
        if ( graph[go_to.first - 1][go_to.second] != -1 && visited[graph[go_to.first - 1][go_to.second]] == 0
             && tmp != st_index) {
            q.push(tmp);
            visited[graph[go_to.first - 1][go_to.second]] = visited[graph[go_to.first][go_to.second]] + 1;
        }
        //R
        tmp = make_pair(go_to.first, go_to.second + 1);
        if ( graph[go_to.first][go_to.second + 1] != -1 && visited[graph[go_to.first][go_to.second + 1]] == 0
             && tmp != st_index) {
            q.push(tmp);
            visited[graph[go_to.first][go_to.second + 1]] = visited[graph[go_to.first][go_to.second]] + 1;
        }

    }


}


int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("input.txt");
    ofstream output("output.txt");

    input.tie(nullptr);

    int hight, width;

    input >> hight >> width;
    vector<vector<int>> graph(hight + 2);
    for (int i = 0; i < width + 2; i++){
        graph[0].push_back(-1);
        graph[hight + 1].push_back(-1);
    }



    pair<int, int> start_ind;
    int start = -1;
    pair<int, int> end_ind;
    int end = -1;

    int index = 0;
    for (int i = 1; i < hight + 1; i++){
        graph[i].push_back(-1);
        for(int j = 0; j < width; j++){
            char tmp;
            input >> tmp;
            if(tmp != '#'){
                graph[i].push_back(index++);
                if (tmp == 'S') {
                    start_ind = make_pair(i, j + 1);
                    start = index - 1;
                }
                if (tmp == 'T') {
                    end_ind = make_pair(i, j + 1);
                    end = index - 1;
                }
            } else {
                graph[i].push_back(-1);
            }

        }
        graph[i].push_back(-1);
    }
    vector<int>  visited(index);

    string str = "";

    BFS(graph, end_ind, start_ind, visited);

    if (!visited[start]){
        output << -1;
        return 0;
    } else {
        output << visited[start] << '\n';
    }

    if (visited[start]){
        int weight = visited[start];
        queue <pair<int, int>> m;
        m.push(start_ind);
        while (weight!= 0){
            pair<int, int> go_to = m.front();
            m.pop();
            if (graph[go_to.first][go_to.second - 1] != -1 &&
            visited[graph[go_to.first][go_to.second - 1]] == visited[graph[go_to.first][go_to.second]]- 1 ){
                m.push(make_pair(go_to.first, go_to.second - 1));
                weight --;
                str += 'L';
            } else if (graph[go_to.first + 1][go_to.second] != -1 &&
            visited[graph[go_to.first + 1][go_to.second]] == visited[graph[go_to.first][go_to.second]] - 1){
                m.push(make_pair(go_to.first + 1, go_to.second));
                weight --;
                str += 'D';
            } else if (graph[go_to.first - 1][go_to.second] != -1 &&
            visited [graph[go_to.first - 1][go_to.second]] == visited[graph[go_to.first][go_to.second]] - 1){
                m.push(make_pair(go_to.first - 1, go_to.second));
                weight --;
                str += 'U';
            } else if (graph[go_to.first][go_to.second + 1] != -1 &&
            visited[graph[go_to.first][go_to.second + 1]] == visited[graph[go_to.first][go_to.second]] - 1){
                m.push(make_pair(go_to.first, go_to.second + 1));
                weight --;
                str += 'R';
            }

        }
        output << str;
    }

    return 0;
}