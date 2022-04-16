#include <bits/stdc++.h>

using namespace std;
int n;
bool chk(vector<int> &A){
    int m = A.size();
    if (m<=3) return 1;
    for (int i=2; i<=m/2; ++i){
        int cnt = 0; int mx = 0;
        for (int j=0; j+i<m;++j) {
            if (A[j] == A[i+j]) {
                cnt++; if (cnt == i) return 0;
            } 
            else cnt = 0;
        } 
    }
    return 1;
}


bool bt(int p, vector<int> &num){
    if (num.size() == n) return chk(num);
    for (int i=1; i<=3; ++i) if (i!=p){
        num.push_back(i);
        if (chk(num) && bt(i, num)) return 1;
        num.pop_back();
    }
    return 0;
}

int main()
{
    cin >> n;
    vector<int> num;
    bt(-1, num);
    for (auto x : num) cout << x;
} // namespace std;
