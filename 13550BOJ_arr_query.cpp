#include <math.h>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <tuple>

using ull = unsigned long long;
using namespace std;
typedef tuple<int, int, int> intp;
int n, k, m;
int sn;
vector<ull> pre;
vector<int> cnt;
vector<int> cnt_sq;
vector<intp> qry;
vector<list<int>> now;

bool comp(intp &a, intp &b)
{
    if (get<0>(a) / sn == get<0>(b) / sn)
        return get<1>(a) < get<1>(b);
    else
        return get<0>(a) < get<0>(b);
}

void insert(int x){
    ull y = pre[x];
    list<int> &d = now[y];
    if (d.empty()){
        d.push_back(x);
        cnt[0] ++; cnt_sq[0] ++;
    } else {
        int lm = d.back() - d.front();
        if (x < d.front()) d.push_front(x);
        else d.push_back(x);
        int nm = d.back() - d.front();
        cnt[lm] --; cnt_sq[lm/sn] --;
        cnt[nm] ++; cnt_sq[nm/sn] ++;
    }
}

void remove(int x){
    ull y = pre[x];
    list<int> &d = now[y];
    int lm = d.back() - d.front();
    cnt[lm] --; cnt_sq[lm/sn] --;
    if (d.front() == x) d.pop_front();
    else d.pop_back();
    if (!d.empty()){
        int nm = d.back() - d.front();
        cnt[nm] ++; cnt_sq[nm/sn] ++;
    }
}

int find_max(){
    int i,j;
    for (i=sn; i>=0; i--){
        if (cnt_sq[i]) break;
    }
    int k= min(n,(i+1)*sn-1);
    for (j=k; j>=i*sn; j--){
        if (cnt[j]) return j;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    cin >> k;
    sn = (int)sqrt(n + 1) + 1;
    cnt.resize(n+1);
    cnt_sq.resize(sn+1);
    pre.resize(n+1);
    now.resize(k);
    for (int i = 0; i < n; i++)
    {
        ull x;
        cin >> x;
        pre[i+1] += (pre[i] + x)%k;
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        qry.push_back(make_tuple(a-1,b,i));
    }
    sort(qry.begin(), qry.end(), comp);
    vector<int> result(m);
    int li=get<0>(qry[0]), lj=get<1>(qry[0]), lk=get<2>(qry[0]);
    for (int i=li; i<=lj; i++) insert(i);
    result[lk] = find_max();
    for (int w=1; w<m; w++){
        int ni=get<0>(qry[w]), nj=get<1>(qry[w]),nk=get<2>(qry[w]);
        if (ni/sn == li/sn){
            for (int x=lj+1; x<=nj; x++) insert(x);
            if (li<ni){
                for (int x=li; x<ni; x++) remove(x);
            } else {
                for (int x=li-1; x>=ni; x--) insert(x);
            }
        } else {
            if (lj<nj){
                for (int x=lj+1; x<=nj; x++) insert(x);
            } else{
                for (int x=lj; x>nj; x--) remove(x);
            }
            for (int x=li; x<ni; x++) remove(x);
        }
        li = ni; lj = nj;
        result[nk] = find_max();
    }
    for (int x : result){
        cout << x << '\n';
    }

} // namespace std;
