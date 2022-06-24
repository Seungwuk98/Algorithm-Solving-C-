#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

struct Info { int u, v, state; };

struct UnionFind {
	vector<int> parent, rank;
	stack<Info> S;
	UnionFind(int n) : parent(n), rank(n, 1) {
		iota(parent.begin(), parent.end(), 0);
	}
	int Find(int x) {
		return x == parent[x] ? x : Find(parent[x]);
	}
	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return 0;
		if (rank[a] < rank[b]) swap(a, b);
		S.push({ a, b, rank[a] == rank[b] });
		parent[b] = a;
		rank[a] += rank[a] == rank[b];
		return 1;
	}
	void rollback(int cnt) {
		while (cnt--) {
			auto [a, b, flag] = S.top(); S.pop();
			parent[b] = b;
			rank[a] -= flag;
		}
	}
};

using pii = pair<int, int>;

struct SegTree {
	vector<vector<pii>> tree;
	SegTree(int n) : tree(4 * n) {}
	void add(int node, int tree_l, int tree_r, int elem_l, int elem_r, pii info) {
		if (tree_r < elem_l || elem_r < tree_l) return;
		if (elem_l <= tree_l && tree_r <= elem_r) {
			tree[node].push_back(info);
			return;
		}
		int mid = tree_l + tree_r >> 1;
		add(node << 1, tree_l, mid, elem_l, elem_r, info);
		add(node << 1 | 1, mid + 1, tree_r, elem_l, elem_r, info);
	}
};

void sol(vector<pii>& q, UnionFind& UF, SegTree& ST, int node, int l, int r) {
	int cnt = 0;
	for (auto [a, b] : ST.tree[node]) cnt += UF.Union(a, b);
	if (l == r) {
		cout << (UF.Find(q[l].first) == UF.Find(q[l].second)) << '\n';
		UF.rollback(cnt);
		return;
	}
	int mid = l + r >> 1;
	sol(q, UF, ST, node << 1, l, mid);
	sol(q, UF, ST, node << 1 | 1, mid + 1, r);
	UF.rollback(cnt);
}

int main() {
	fastio;
	int n, m, cnt = 0, cnt2 = 0; cin >> n >> m;
	vector<tuple<int, int, int>> v;
	while (m--) {
		int t, a, b; cin >> t >> a >> b;
		if (a > b) swap(a, b);
		if (t == 3) cnt++;
		v.push_back({ t, a, b });
	}
	UnionFind UF(n + 1); SegTree ST(cnt);
	vector<pii> q; map<pii, int> M;
	for (auto [t, a, b] : v) {
		if (t == 1) M[{a, b}] = cnt2;
		if (t == 2) ST.add(1, 0, cnt - 1, M[{a, b}], cnt2 - 1, { a, b }), M.erase({ a, b });
		if (t == 3) q.push_back({ a, b }), cnt2++;
	}
	for (auto [key, val] : M) ST.add(1, 0, cnt - 1, val, cnt - 1, key);
	sol(q, UF, ST, 1, 0, cnt - 1);
}