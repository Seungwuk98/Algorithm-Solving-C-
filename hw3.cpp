#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()

using namespace std;

/******** edge의 정보를 담기 위한 객체 ********/
struct edge{
    int s, e;
};
/**********************************************/


class Scc_adj_array {
private :
    /************* 인스턴스 변수 *************/
    vector<vector<int>>     adj;        // 정방향 인접 리스트(array)            
    vector<vector<int>>     adj_inv;    // 역방향 인접 리스트(array)            
    vector<int>             pos;        // post order 순으로 들어간 정점의 번호 
    vector<bool>            vst;        // 각 정점을 방문 했는지 확인           
    vector<vector<string>>  sccs;       // scc 각각을 vector로서 저장           
    int     v,e;                        // v : 정점의 개수, e : 간선의 개수     
    double  T;                          // 소요 시간                            
    /************* 인스턴스 변수 *************/


    /*****************************************
     * 각 정점을 post order로 방문한 순서대로 pos 벡터에 저장 
    ******************************************/
    void dfs1(int node) {
        for (auto nxt : adj[node]) {
            if (!vst[nxt]) {
                vst[nxt] = 1;
                dfs1(nxt);
            }
        }
        pos.push_back(node);
    }
    
    /*****************************************
     * post order의 내림차순으로 dfs2를 호출
     * 이 때 방문한 모든 노드가 하나의 scc가 됨
    ******************************************/
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
    /******************************************
     * 정점의 개수, 간선의 개수, 간선의 정보들을 받아 scc를 생성합니다.
    *******************************************/
    Scc_adj_array(int v, int e, vector<edge> &E)
        : v(v), e(e) {
        /********* 그래프 설정 및 초기화 *********/
        adj.resize(v+1); adj_inv.resize(v+1); vst.resize(v+1);
        for (int i=0; i<e; ++i) {
            adj[E[i].s].push_back(E[i].e);
            adj_inv[E[i].e].push_back(E[i].s);
        }
        /********* 그래프 설정 및 초기화 *********/

        clock_t start = clock();
        /************** 첫 번째 dfs **************/
        for (int i=1; i<=v; ++i){
            if (!vst[i]) {
                vst[i] = 1;
                dfs1(i);
            }
        }
        /************** 첫 번째 dfs **************/
        

        // string으로 저장된 scc를 int 순으로 비교하기 위한 compare 함수
        auto int_comp = [&](string &a, string &b) {return stoi(a) < stoi(b);};
        // 방문배열 초기화
        fill(vst.begin()+1, vst.end(), 0);


        /************** 두 번째 dfs **************/
        for (int i=v-1; i>=0; --i) {
            if (!vst[pos[i]]) {
                vst[pos[i]] = 1;
                vector<string> scc;
                dfs2(pos[i], scc);
                sort(all(scc), int_comp);
                sccs.push_back(scc);
            }
        }
        /************** 두 번째 dfs **************/

        sort(all(sccs));
        // 시간 측정
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
    /************* 인스턴스 변수 *************/
    vector<list<int>> adj;          // 정방향 인접 리스트(linked list)
    vector<list<int>> adj_inv;      // 역방향 인접 리스트(linked list)
    vector<int> pos;                // post order 순으로 들어간 정점의 번호 
    vector<bool> vst;               // 각 정점을 방문 했는지 확인  
    vector<vector<string>> sccs;    // scc 각각을 vector로서 저장  
    int v,e;                        // v : 정점의 개수, e : 간선의 개수 
    double T;                       // 소요 시간    
    /************* 인스턴스 변수 *************/

    /*****************************************
     * 각 정점을 post order로 방문한 순서대로 pos 벡터에 저장 
    ******************************************/
    void dfs1(int node) {
        for (auto nxt : adj[node]) {
            if (!vst[nxt]) {
                vst[nxt] = 1;
                dfs1(nxt);
            }
        }
        pos.push_back(node);
    }

    /*****************************************
     * post order의 내림차순으로 dfs2를 호출
     * 이 때 방문한 모든 노드가 하나의 scc가 됨
    ******************************************/
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
    /******************************************
     * 정점의 개수, 간선의 개수, 간선의 정보들을 받아 scc를 생성합니다.
    *******************************************/
    Scc_adj_list(int v, int e, vector<edge> &E)
        : v(v), e(e) {
        /********* 그래프 설정 및 초기화 *********/
        adj.resize(v+1); adj_inv.resize(v+1);
        vst.resize(v+1);
        for (int i=0; i<e; ++i) {
            adj[E[i].s].push_back(E[i].e);
            adj_inv[E[i].e].push_back(E[i].s);
        }
        /********* 그래프 설정 및 초기화 *********/

        clock_t start = clock();
        /************** 첫 번째 dfs **************/
        for (int i=1; i<=v; ++i){
            if (!vst[i]) {
                vst[i] = 1;
                dfs1(i);
            }
        }
        /************** 첫 번째 dfs **************/

        // string으로 저장된 scc를 int 순으로 비교하기 위한 compare 함수
        auto int_comp = [&](string &a, string &b) {return stoi(a) < stoi(b);};
        // 방문배열 초기화
        fill(vst.begin()+1, vst.end(), 0);

        /************** 두 번째 dfs **************/
        for (int i=v-1; i>=0; --i) {
            int t = pos[i];
            if (!vst[t]) {
                vst[t] = 1;
                vector<string> scc;
                dfs2(t, scc);
                sort(all(scc), int_comp);
                sccs.push_back(scc);
            }
        }
        /************** 두 번째 dfs **************/
        sort(all(sccs));

        // 시간 측정
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
    /************* bit set *************/
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
    /************* bit set *************/

    /************* 인스턴스 변수 *************/
    vector<bset> adj;               // 정방향 인접 행렬
    vector<bset> adj_inv;           // 역방향 인접 행렬
    vector<int> pos;                // post order 순으로 들어간 정점의 번호 
    vector<bool> vst;               // 각 정점을 방문 했는지 확인 
    vector<vector<string>> sccs;    // scc 각각을 vector로서 저장
    int v,e;                        // v : 정점의 개수, e : 간선의 개수 
    double T;                       // 소요 시간 
    /************* 인스턴스 변수 *************/

    /*****************************************
     * 각 정점을 post order로 방문한 순서대로 pos 벡터에 저장
     * 이 때, 모든 정점을 확인하며 인접 행렬의 값이 유효한지 확인 
    ******************************************/
    void dfs1(int node) {
        for (int nxt = 1; nxt <= v; ++nxt) {
            if (adj[node][nxt] && !vst[nxt]) {
                vst[nxt] = 1;
                dfs1(nxt);
            }
        }
        pos.push_back(node);
    }

    /*****************************************
     * post order의 내림차순으로 dfs2를 호출
     * 이 때 방문한 모든 노드가 하나의 scc가 됨
     * 이 때, 모든 정점을 확인하며 인접 행렬의 값이 유효한지 확인 
    ******************************************/
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
    /******************************************
     * 정점의 개수, 간선의 개수, 간선의 정보들을 받아 scc를 생성합니다.
    *******************************************/
    Scc_adj_matrix(int v, int e, vector<edge> &E)
        : v(v), e(e) {
        /********* 그래프 설정 및 초기화 *********/
        adj.resize(v+1); adj_inv.resize(v+1);
        vst.resize(v+1);
        for (int i=1; i<=v; ++i) {
            adj[i].resize(v+1);
            adj_inv[i].resize(v+1);
        }
        for (int i=0; i<e; ++i) {
            // 인접 행렬 설정
            adj[E[i].s].set(E[i].e);
            adj_inv[E[i].e].set(E[i].s);
        }
        /********* 그래프 설정 및 초기화 *********/
  
        clock_t start = clock();

        /************** 첫 번째 dfs **************/
        for (int i=1; i<=v; ++i){
            if (!vst[i]) {
                vst[i] = 1;
                dfs1(i);
            }
        }
        /************** 첫 번째 dfs **************/

        // string으로 저장된 scc를 int 순으로 비교하기 위한 compare 함수
        auto int_comp = [&](string &a, string &b) {return stoi(a) < stoi(b);};
        // 방문 배열 초기화
        fill(vst.begin()+1, vst.end(), 0);

        /************** 두 번째 dfs **************/
        for (int i=v-1; i>=0; --i) {
            int t = pos[i];
            if (!vst[t]) {
                vst[t] = 1;
                vector<string> scc;
                dfs2(t, scc);
                sort(all(scc), int_comp);
                sccs.push_back(scc);
            }
        }
        /************** 두 번째 dfs **************/
        sort(all(sccs));

        // 시간 측정
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
    /************** 파일 입출력 *************/
    ifstream cin_input;
    ofstream cout_adj;
    cin_input.open(argv[1]);
    cout_adj.open(argv[2]);
    /************** 파일 입출력 *************/

    /*********** 그래프 정보 입력 ************/    
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
    /*********** 그래프 정보 입력 ************/    

    /*********** 각 경우에 따라 scc와 수행 시간을 전달 받음 ***********/
    vector<vector<string>> scc;
    double Time;
    if (strcmp(argv[3], "adj_mat") == 0) {
        Scc_adj_matrix scc_adj(v, e, E);
        scc = scc_adj.get_scc();
        Time = scc_adj.get_time();
    } 
    else if (strcmp(argv[3], "adj_list") == 0) {
        Scc_adj_list scc_adj(v, e, E);
        scc = scc_adj.get_scc();
        Time = scc_adj.get_time();
    }
     else {
        Scc_adj_array scc_adj(v, e, E);
        scc = scc_adj.get_scc();
        Time = scc_adj.get_time();
    }
    /*********** 각 경우에 따라 scc와 수행 시간을 전달 받음 ***********/

    /********* 출력 *********/
    for (auto x : scc) {
        for (auto y : x) cout_adj << y << ' ';
        cout_adj << '\n';
    }
    cout_adj << Time << "ms";
    /********* 출력 *********/

    /********* 입출력 종료 *********/
    cin_input.close();
    cout_adj.close();
    /********* 입출력 종료 *********/
}