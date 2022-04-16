#include <string>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

string a,b;
string result;

void lcs(int l1, int l2, int r1, int r2){
    if (r1>r2) return;
    if (l1 == l2){
        for (int i=r1; i<=r2; ++i){
            if (a[l1] == b[i]){
                result.push_back(b[i]); break;
            }
        }
        return;
    }
    int mid = l1 + l2 >> 1;
    vector<int> lcs1(r2-r1+3,0), lcs2(r2-r1+3,0), prev(r2-r1+3,0);
    for (int i=l1; i<=mid; ++i){
        for (int j=r1; j<=r2; ++j){
            int nj = j-r1+1;
            if (a[i] == b[j]) lcs1[nj] = prev[nj-1]+1;
            else lcs1[nj] = max(prev[nj], lcs1[nj-1]);
        }
        prev = lcs1;
    }
    fill(prev.begin(), prev.end(), 0);
    for (int i=l2; i>mid; --i){
        for (int j=r2; j>=r1; --j){
            int nj = j-r1+1;
            if (a[i] == b[j]) lcs2[nj] = prev[nj+1]+1;
            else lcs2[nj] = max(prev[nj], lcs2[nj+1]);
        }
        prev = lcs2;
    }

    int mlcs=-1, idx = 0;
    for (int i=r1-1; i<=r2; ++i){
        int ni = i-r1+1;
        int l = lcs1[ni] + lcs2[ni+1];
        if (mlcs < l) {
            mlcs = l; idx = i;
        }
    }

    lcs(l1,mid,r1,idx);
    lcs(mid+1,l2,idx+1,r2);
}



int main()
{
    int n,m;
    cin >> n >> m;
    cin >> a >> b;
    lcs(0, n-1, 0, m-1);
    cout << result.size() << '\n' << result;

} // namespace std;
