#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
vector<int> prefix_function(string s){
    int n = (int) s.size();
    vector<int> result (n);
    for(int i = 1; i < n; i++){
        int k = result[i - 1];
        while (k > 0 && s[i] != s[k]){
            k = result[k-1];
        }
        if (s[i] == s[k]){
            result [i] = k + 1;
        }
        else
            result[i] = k;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("prefix.in");
    ofstream output("prefix.out");


    input.tie(nullptr);

    string text;
    getline(input, text);

    vector<int> ans = prefix_function(text);
    for (auto i : ans){
        output << i << ' ';
    }
    return 0;
}