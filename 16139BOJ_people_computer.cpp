#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

string s;
int n, q;
int pre[26][202020] = {0,};


int main() {
    fastio
    cin >> s;
    n = s.size();
    for (int i=0; i<n; ++i) {
        for (int j=0; j<26; ++j) pre[j][i+1] = pre[j][i];
        pre[s[i]-'a'][i+1]++;
    }
    
    cin >> q;
    while (q--) {
        char a; int b, c;
        cin >> a >> b >> c;
        cout << pre[a-'a'][c+1]-pre[a-'a'][b] << ' ';
    }


}