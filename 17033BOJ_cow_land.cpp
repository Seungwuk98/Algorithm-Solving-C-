//구현 2. mmap/write 이용
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Author : jinhan814
 * Date : 2021-05-06
 * Source : https://blog.naver.com/jinhan814/222266396476
 * Description : FastIO implementation for cin, cout. (mmap ver.)
 */
constexpr int SZ = 1 << 20;

class INPUT {
private:
    char* p;
    bool __END_FLAG__, __GETLINE_FLAG__;
public:
    explicit operator bool() { return !__END_FLAG__; }
    INPUT() {
        struct stat st; fstat(0, &st);
        p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
    }
    bool IsBlank(char c) { return c == ' ' || c == '\n'; }
    bool IsEnd(char c) { return c == '\0'; }
    char _ReadChar() { return *p++; }
    char ReadChar() {
        char ret = _ReadChar();
        for (; IsBlank(ret); ret = _ReadChar());
        return ret;
    }
    template<typename T> T ReadInt() {
        T ret = 0; char cur = _ReadChar(); bool flag = 0;
        for (; IsBlank(cur); cur = _ReadChar());
        if (cur == '-') flag = 1, cur = _ReadChar();
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret = 10 * ret + (cur & 15);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return flag ? -ret : ret;
    }
    string ReadString() {
        string ret; char cur = _ReadChar();
        for (; IsBlank(cur); cur = _ReadChar());
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (IsEnd(cur)) __END_FLAG__ = 1;
        return ret;
    }
    double ReadDouble() {
        string ret = ReadString();
        return stod(ret);
    }
    string getline() {
        string ret; char cur = _ReadChar();
        for (; cur != '\n' && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
        if (__GETLINE_FLAG__) __END_FLAG__ = 1;
        if (IsEnd(cur)) __GETLINE_FLAG__ = 1;
        return ret;
    }
    friend INPUT& getline(INPUT& in, string& s) { s = in.getline(); return in; }
} _in;

class OUTPUT {
private:
    char write_buf[SZ];
    int write_idx;
public:
    ~OUTPUT() { Flush(); }
    explicit operator bool() { return 1; }
    void Flush() {
        write(1, write_buf, write_idx);
        write_idx = 0;
    }
    void WriteChar(char c) {
        if (write_idx == SZ) Flush();
        write_buf[write_idx++] = c;
    }
    template<typename T> int GetSize(T n) {
        int ret = 1;
        for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;
        return ret;
    }
    template<typename T> void WriteInt(T n) {
        int sz = GetSize(n);
        if (write_idx + sz >= SZ) Flush();
        if (n < 0) write_buf[write_idx++] = '-', n = -n;
        for (int i = sz; i --> 0; n /= 10) write_buf[write_idx + i] = n % 10 | 48;
        write_idx += sz;
    }
    void WriteString(string s) { for (auto& c : s) WriteChar(c); }
    void WriteDouble(double d) { WriteString(to_string(d)); }
} _out;

/* operators */
INPUT& operator>> (INPUT& in, char& i) { i = in.ReadChar(); return in; }
INPUT& operator>> (INPUT& in, string& i) { i = in.ReadString(); return in; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
INPUT& operator>> (INPUT& in, T& i) {
    if constexpr (is_floating_point_v<T>) i = in.ReadDouble();
    else if constexpr (is_integral_v<T>) i = in.ReadInt<T>(); return in; }

OUTPUT& operator<< (OUTPUT& out, char i) { out.WriteChar(i); return out; }
OUTPUT& operator<< (OUTPUT& out, string i) { out.WriteString(i); return out; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
OUTPUT& operator<< (OUTPUT& out, T i) {
    if constexpr (is_floating_point_v<T>) out.WriteDouble(i);
    else if constexpr (is_integral_v<T>) out.WriteInt<T>(i); return out; }

/* macros */
#define fastio 1
#define cin _in
#define cout _out
#define istream INPUT
#define ostream OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

vector<int> sz, top, dep, pr, in;
vector<ll> arr, narr;
vector<bool> vst;
vector<vector<int>> g;
int n, q, pv=0;



struct Node
{
    int lo, hi;
    long sum, lazy;
    Node *l, *r;
    Node(int lo, int hi) : lo(lo), hi(hi){
        l=r=nullptr;
        sum=0; lazy=-1;
    }
};


struct Segtree
{
    vector<ll> tree;
    void init(vector<ll> &arr){
        tree.resize(2*n);
        for (int i=0; i<n; ++i) tree[i+n] = arr[i];
        for (int i=n-1; i>0; --i) tree[i] = tree[i<<1] ^ tree[i<<1|1];
    }

    void update(int i, ll z){
        i += n;
        tree[i] = z;
        while (i>>1){
            tree[i>>1] = tree[i]^tree[i^1];
            i>>=1;
        }
    }

    ll query(int l, int r){
        ll ret = 0;
        for (l+=n, r+=n+1; l<r; l>>=1, r>>=1){
            if (l&1) ret^=tree[l++];
            if (r&1) ret^=tree[--r];
        }
        return ret;
    }
} tree;

void dfs1(int node=1){
    int msz,midx; msz=midx=0;
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (vst[next]) continue;
        vst[next] = 1;
        pr[next] = node;
        dep[next] = dep[node] + 1;
        dfs1(next); sz[node] += sz[next];
        if (sz[next] > msz){
            msz = sz[next]; midx = i;
        }
    }
    if (!g[node].empty()) swap(g[node][0], g[node][midx]);
}

void dfs2(int node=1){
    in[node] = pv;
    narr[pv++] = arr[node-1];
    for (int i=0; i<g[node].size(); ++i){
        int next = g[node][i];
        if (vst[next]) continue;
        vst[next] = 1;
        top[next] = i? next : top[node];
        dfs2(next);
    }
}

ll query(int x, int y){
    ll ret = 0;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x,y);
        int st = top[x];
        ret ^= tree.query(in[st], in[x]);
        x = pr[st];
    }
    if (dep[x] > dep[y]) swap(x,y);
    ret ^= tree.query(in[x], in[y]);
    return ret;
}

int main()
{
    cin >> n >> q; 
    sz.resize(n+1,1); top.resize(n+1,1); pr.resize(n+1); dep.resize(n+1);
    g.resize(n+1); vst.resize(n+1); in.resize(n+1); arr.resize(n); narr.resize(n);
    for (int i=0; i<n; ++i) cin >> arr[i];
    for (int i=n-1;i--;){
        int x,y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    vst[1] = 1;
    dfs1();
    vst.assign(n+1,0);
    vst[1] = 1;
    dfs2();


    tree.init(narr);
    while (q--){
        ll z, x, y;
        cin >> z >> x >> y;
        if (z==1) {
            tree.update(in[x],y);
        } else {
            cout << query(x,y) << '\n';
        }
        
    }
} // namespace std;
