#include <bits/stdc++.h>

using namespace std;
int l;

vector<string> sol(vector<string> &input, int n) {
    if (n == l) return input;
    vector<string> ret(n*3);
    for (int i=0; i<n; ++i) for (int j=0; j<3; ++j) {
        ret[i] += input[i];
        ret[n*2+i] += input[i];
    }
    for (int i=0; i<n; ++i) ret[n+i] += input[i];
    for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) ret[n+i] += " ";
    for (int i=0; i<n; ++i) ret[n+i] += input[i];
    return sol(ret, n*3);
}


int main() {
    vector<string> a = {
        "***",
        "* *",
        "***"
    };
    cin >> l;
    vector<string> ans = sol(a, 3);
    for (auto x : ans) cout << x << '\n';

}