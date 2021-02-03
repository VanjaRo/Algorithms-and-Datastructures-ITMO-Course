#include <iostream>
#include <vector>
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

    
    
    string text;
    int power;
    cin >> power;
    cin >> text;
    text += '*';
    vector<int> pref = prefix_function(text);
    vector<vector<int>> aut(text.size(),vector<int>(power));
    for (int i = 0; i < text.size(); i++){
        for( char c = 'a'; c < 'a' + power; c++){
            if( i > 0 && c != text[i])
                aut[i][c - 'a'] = aut[pref[i - 1]][c - 'a'];
            else if ( c == text[i])
                aut[i][c- 'a'] = i + 1;
        }
    }
    for (auto i : aut){
        for(auto j : i){
            cout << j << ' ';
        }
        cout << '\n';
    }
    return 0;
}