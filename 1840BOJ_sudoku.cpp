#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define INF 1000000
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);


using namespace std;
struct node {
	int row;
	int size;
	node* column;
	node* up;
	node* down;
	node* left;
	node* right;
};

void dlx_cover(node* c) {
	c->right->left = c->left;
	c->left->right = c->right;
	for (node* it = c->down; it != c; it = it->down) {
		for (node* jt = it->right; jt != it; jt = jt->right) {
			jt->down->up = jt->up;
			jt->up->down = jt->down;
			jt->column->size--;
		}
	}
}

void dlx_uncover(node* c) {
	for (node* it = c->up; it != c; it = it->up) {
		for (node* jt = it->left; jt != it; jt = jt->left) {
			jt->down->up = jt;
			jt->up->down = jt;
			jt->column->size++;
		}
	}
	c->right->left = c;
	c->left->right = c;
}

bool dlx_search(node* head, int k, vector<int>& solution) {
	if (head->right == head) return 1;
	node* ptr = nullptr;
	int low = INF;
	for (node* it = head->right; it != head; it = it->right) {
		if (it->size < low) {
			if (it->size == 0) return 0;
			low = it->size;
			ptr = it;
		}
	}
	dlx_cover(ptr);
	for (node* it = ptr->down; it != ptr; it = it->down) {
		solution.push_back(it->row);
		for (node* jt = it->right; jt != it; jt = jt->right) {
			dlx_cover(jt->column);
		}
		if (dlx_search(head, k + 1, solution)) return 1;
		else {
			solution.pop_back();
			for (node* jt = it->left; jt != it; jt = jt->left) {
				dlx_uncover(jt->column);
			}
		}
	}
	dlx_uncover(ptr);
	return 0;
}

vector<vector<int>> mat(9);

bool dlx_solve(vector<vector<int>> matrix) {
	int n = matrix[0].size();
	vector<node> column(n);
	node head;
	head.right = &column[0];
	head.left = &column[n - 1];
	for (int i = 0; i < n; ++i) {
		column[i].size = 0;
		column[i].up = &column[i];
		column[i].down = &column[i];
		if (i == 0) column[i].left = &head;
		else column[i].left = &column[i - 1];
		if (i == n - 1) column[i].right = &head;
		else column[i].right = &column[i + 1];
	}

	vector<node*> nodes;
	for (int i = 0; i < matrix.size(); ++i) {
		node* last = nullptr;
		for (int j = 0; j < n; ++j) if (matrix[i][j]) {
			node* now = new node;
			now->row = i;
			now->column = &column[j];
			now->up = column[j].up;
			now->down = &column[j];
			if (last) {
				now->left = last;
				now->right = last->right;
				last->right->left = now;
				last->right = now;
			}
			else {
				now->left = now;
				now->right = now;
			}
			column[j].up->down = now;
			column[j].up = now;
			column[j].size++;
			last = now;
			nodes.push_back(now);
		}
	}
	
	for (int i=0; i<9; ++i){
		for (int j=0; j<9; ++j){
			if (mat[i][j]){
				int k = mat[i][j]-1;
				dlx_cover(&column[i*9+j]);
				dlx_cover(&column[81 + i*9+k]);
				dlx_cover(&column[162 + j*9+k]);
				dlx_cover(&column[243 + (i/3*3+j/3)*9+k]);
			}
		}
	}


	vector<int> solution;
	bool c = dlx_search(&head, 0, solution);
	for (node* ptr: nodes) delete ptr;

	return c;
}

inline int box(int i, int j) {
    return i/3*3+j/3;
}

int main(){
    fastio
    for (int i=0; i<9; ++i) mat[i].resize(9);
    vector<vector<int>> d;
    for (int i=0; i<9; ++i){
        for (int j=0; j<9; ++j){
            for (int k=0; k<9; ++k){
                vector<int> tmp(324);
                tmp[i*9+j] = 1;
                tmp[81 + i*9+k] = 1;
                tmp[162 + j*9+k] = 1;
                tmp[243 + (i/3*3+j/3)*9+k] = 1;
                d.push_back(tmp);
            }
        }
    }
    int qry[3][9] = {0,};
    
    for (int i=1; i<=81; ++i) {
        int x, y, z; cin >> x >> y >> z;
        x--; y--;
        if ((qry[0][x] & (1<<z)) || (qry[1][y] & (1<<z)) || (qry[2][box(x, y)] & (1<<z))) {
            cout << i;
            return 0;
        }
        mat[x][y] = z;
        qry[0][x] |= 1<<z;
        qry[1][y] |= 1<<z;
        qry[2][box(x, y)] |= 1<<z;
        bool ret = dlx_solve(d);
        if (!ret) {
            cout << i;
            return 0;
        }
    }
    cout << -1;

}