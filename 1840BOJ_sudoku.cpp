#include <bits/stdc++.h>

using namespace std;

int mat[9][9] = {0,};
int qry[3][9] = {0,};

inline int box(int i, int j) {
    return i/3*3 + j/3;
}

bool backtracking(int i, int j){
    if (i == 9) return true;
    if (mat[i][j]) return backtracking(i+(j+1)/9, (j+1)%9);

    for (int k=0; k<9; ++k) {
        int t = 1<<k;
        if (qry[0][i] & t || qry[1][j] & t || qry[2][box(i,j)] & t) continue;
        qry[0][i] |= t;
        qry[1][j] |= t;
        qry[2][box(i,j)] |= t;
        mat[i][j] = k+1;
        if (backtracking(i+(j+1)/9, (j+1)%9)) return true;
        qry[0][i] &= ~t;
        qry[1][j] &= ~t;
        qry[2][box(i,j)] &= ~t;
        mat[i][j] = 0;
    }
    return false;
}

using piii = tuple<int,int,int>;

void cpy(int **now) {
    for (int i=0; i<9; ++i) for (int j=0; j<9; ++j) {
        
    }
}

int main()
{
    piii Q[81];    
    for (int i=0; i<81; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        Q[i] = {--x, --y, z};
    }

    int now[9][9] = {0,};

    for (int i=0, j=0; i<81; i=j) {
        auto [x, y, z] = Q[i];
        now[x][y] = z;
        if (!backtracking(0, 0)) {
            cout << i+1;
            break;
        } 
        while (1) {
            auto [u, v, w] = Q[++j];
            if (mat[u][v] != w) break;
            now[u][v] = w;
        }
        j++;
    }

} // namespace std
