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
vector<int> KMP(string sub, string text){
    vector<int> result;
    vector<int> prefix = prefix_function(sub + "#" + text);

    for(int i = 0; i < text.size(); i++){
        if(prefix[sub.size() + 1 + i] == sub.size())
            result.push_back(i - sub.size() + 2);
    }
    return result;
}
int main() {
    ios_base::sync_with_stdio(false);

    ifstream input("search2.in");
    ofstream output("search2.out");


    input.tie(nullptr);

    string sub;
    string text;
    getline(input, sub);
    getline(input, text);

    vector<int> ans = KMP(sub, text);
    output << ans.size() << '\n';
    for (auto i : ans){
        output << i << ' ';
    }
    return 0;
}