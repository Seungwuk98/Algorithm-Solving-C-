#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define next(i, j) i+(j+1)/9, (j+1)%9

using namespace std;

int mat[9][9];
int row[9], col[9], box[9];

int bx(int x, int y){
    return x/3*3 + y/3;
}

bool sudoku(int i, int j){
    if (i == 9) return 1;
    if (mat[i][j]) return sudoku(next(i,j));
    for (int k=0; k<9; ++k){
        int bit = 1 << k;
        if (row[i]&bit || col[j]&bit || box[bx(i,j)]&bit) continue;
        row[i] |= bit;
        col[j] |= bit;
        box[bx(i,j)] |= bit;
        mat[i][j] = k+1;
        if (sudoku(next(i,j))) return 1;
        row[i] &= ~bit;
        col[j] &= ~bit;
        box[bx(i,j)] &= ~bit;
        mat[i][j] = 0;
    }
    return 0;
}

int main(){
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(row));
    memset(box, 0, sizeof(row));
    for (int i=0; i<9; ++i){
        for (int j=0; j<9; ++j) cin >> mat[i][j];
    }
    
    for (int i=0; i<9; ++i) for (int j=0; j<9; ++j) if (mat[i][j]){
        int bit = 1 << mat[i][j]-1;
        row[i] |= bit;
        col[j] |= bit;
        box[bx(i,j)] |= bit;
    }
    bool check = sudoku(0, 0);
    for (int i=0; i<9; ++i) {
        for (int j=0; j<9; ++j) cout << mat[i][j] << ' ';
        cout << '\n';
    }
}