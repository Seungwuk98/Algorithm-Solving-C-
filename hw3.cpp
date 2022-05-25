#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()

using namespace std;

struct edge{
    int s, e;

    friend istream& operator>>(istream &is, edge &e) {
        is >> e.s >> e.e;
        return is;
    }
};


class Scc_adj_array {
private :
    vector<vector<int>> adj;
    vector<vector<int>> adj_inv;
    vector<int> pos;
    vector<bool> vst;
    vector<vector<string>> sccs;
    int v,e;
    double T;
    void dfs1(int node) {
        for (auto nxt : adj[node]) {
            if (!vst[nxt]) {
                vst[nxt] = 1;
                dfs1(nxt);
            }
        }
        pos.push_back(node);
    }
    void dfs2(int node, vector<string> &scc) {
        scc.push_back(to_string(node));
        for (auto nxt : adj_inv[node]) {
            if (!vst[nxt]) {
                vst[nxt] = 1;
                dfs2(nxt, scc);
            }
        }
    }
public:
    Scc_adj_array(int v, int e, vector<edge> &E)
        : v(v), e(e) {
        adj.resize(v+1); adj_inv.resize(v+1); 
        vst.resize(v+1);
        for (int i=0; i<e; ++i) {
            adj[E[i].s].push_back(E[i].e);
            adj_inv[E[i].e].push_back(E[i].s);
        }

        clock_t start = clock();
        for (int i=1; i<=v; ++i){
            if (!vst[i]) {
                vst[i] = 1;
                dfs1(i);
            }
        }
        auto int_comp = [&](string &a, string &b) {return stoi(a) < stoi(b);};
        fill(vst.begin()+1, vst.end(), 0);

        for (int i=v-1; i>=0; --i) {
            if (!vst[pos[i]]) {
                vst[pos[i]] = 1;
                vector<string> scc;
                dfs2(pos[i], scc);
                // sort(all(scc), int_comp);
                sccs.push_back(scc);
            }
        }
        // sort(all(sccs));
        clock_t end = clock();
        T = (double) end - start;
    }
    vector<vector<string>>& get_scc() {
        return sccs;
    }

    double get_time() {
        return T;
    }
};

class Scc_adj_list {
private :
    vector<list<int>> adj;
    vector<list<int>> adj_inv;
    vector<int> pos;
    vector<bool> vst;
    vector<vector<string>> sccs;
    int v,e;
    double T;
    void dfs1(int node) {
        for (auto nxt : adj[node]) {
            if (!vst[nxt]) {
                vst[nxt] = 1;
                dfs1(nxt);
            }
        }
        pos.push_back(node);
    }
    void dfs2(int node, vector<string> &scc) {
        scc.push_back(to_string(node));
        for (auto nxt : adj_inv[node]) {
            if (!vst[nxt]) {
                vst[nxt] = 1;
                dfs2(nxt, scc);
            }
        }
    }
public:
    Scc_adj_list(int v, int e, vector<edge> &E)
        : v(v), e(e) {
        adj.resize(v+1); adj_inv.resize(v+1);
        vst.resize(v+1);
        for (int i=0; i<e; ++i) {
            adj[E[i].s].push_back(E[i].e);
            adj_inv[E[i].e].push_back(E[i].s);
        }
        clock_t start = clock();
        for (int i=1; i<=v; ++i){
            if (!vst[i]) {
                vst[i] = 1;
                dfs1(i);
            }
        }
        auto int_comp = [&](string &a, string &b) {return stoi(a) < stoi(b);};
        fill(vst.begin()+1, vst.end(), 0);

        for (int i=v-1; i>=0; --i) {
            int t = pos[i];
            if (!vst[t]) {
                vst[t] = 1;
                vector<string> scc;
                dfs2(t, scc);
                // sort(all(scc), int_comp);
                sccs.push_back(scc);
            }
        }
        // sort(all(sccs));
        clock_t end = clock();
        T = (double) end - start;
    }
    vector<vector<string>>& get_scc() {
        return sccs;
    }
    double get_time(){
        return T;
    }
};

class Scc_adj_matrix {
private :
    struct bset {
        private:
            vector<unsigned long long> table;
            int size;

        public:
            bset() { }
            void resize(int n) {
                size = n/64+1;
                table.resize(size);
            }
            bool operator[] (int i) { return table[i/64] & (1LL << (i%64)); }
            void set(int i) { table[i/64] |= 1LL << (i%64); }
    
    };
    vector<bset> adj;
    vector<bset> adj_inv;
    vector<int> pos;
    vector<bool> vst;
    vector<vector<string>> sccs;
    int v,e;
    double T;

    void dfs1(int node) {
        for (int nxt = 1; nxt <= v; ++nxt) {
            if (adj[node][nxt] && !vst[nxt]) {
                vst[nxt] = 1;
                dfs1(nxt);
            }
        }
        pos.push_back(node);
    }
    void dfs2(int node, vector<string> &scc) {
        scc.push_back(to_string(node));
        for (int nxt = 1; nxt <= v; ++nxt) {
            if (adj_inv[node][nxt] && !vst[nxt]) {
                vst[nxt] = 1;
                dfs2(nxt, scc);
            }
        }
    }
public:
    Scc_adj_matrix(int v, int e, vector<edge> &E)
        : v(v), e(e) {
        adj.resize(v+1); adj_inv.resize(v+1);
        vst.resize(v+1);
        for (int i=1; i<=v; ++i) {
            adj[i].resize(v+1);
            adj_inv[i].resize(v+1);
        }
        for (int i=0; i<e; ++i) {
            adj[E[i].s].set(E[i].e);
            adj_inv[E[i].e].set(E[i].s);
        }
        clock_t start = clock();
        for (int i=1; i<=v; ++i){
            if (!vst[i]) {
                vst[i] = 1;
                dfs1(i);
            }
        }
        auto int_comp = [&](string &a, string &b) {return stoi(a) < stoi(b);};
        fill(vst.begin()+1, vst.end(), 0);
        for (int i=v-1; i>=0; --i) {
            int t = pos[i];
            if (!vst[t]) {
                vst[t] = 1;
                vector<string> scc;
                dfs2(t, scc);
                // sort(all(scc), int_comp);
                sccs.push_back(scc);
            }
        }
        // sort(all(sccs));
        clock_t end = clock();
        T = (double) end - start;
    }
    vector<vector<string>>& get_scc() {
        return sccs;
    }

    double get_time(){
        return T;
    }
};


int main(int argc, char* argv[]){
    /***********************************/
    ifstream cin_input;
    ofstream cout_adj;
    cin_input.open(argv[1]);
    cout_adj.open(argv[2]);
    /***********************************/
    
    int v;
    cin_input >> v;
    vector<edge> E;
    for (int s=1; s<=v; ++s) {
        int j; cin_input >> j;
        while (j--){
            int e; cin_input >> e;
            E.push_back({s,e});
        }
    }
    int e = E.size();

    vector<vector<string>> scc;
    double Time;
    if (strcmp(argv[3], "adj_mat") == 0) {
        Scc_adj_matrix scc_adj(v, e, E);
        scc = scc_adj.get_scc();
        Time = scc_adj.get_time();
    } else if (strcmp(argv[3],"adj_list") == 0) {
        Scc_adj_list scc_adj(v, e, E);
        scc = scc_adj.get_scc();
        Time = scc_adj.get_time();
    } else {
        Scc_adj_array scc_adj(v, e, E);
        scc = scc_adj.get_scc();
        Time = scc_adj.get_time();
    }

    for (auto x : scc) {
        for (auto y : x) cout_adj << y << ' ';
        cout_adj << '\n';
    }
    cout_adj << Time << "ms";
}