#include<algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Segment Tree Beats (Task 3)
// - l<=i<r について a_i の値を min(a_i, x) に更新
// - l<=i<r について a_i の値を max(a_i, x) に更新
// - l<=i<r について a_i の値を a_i+x に更新
// - l<=i<r の b_i の和を求める
//
// 各クエリで、a_i が変化した場合に b_i に1加算する

#define N 505050

class SegmentTree {
    const ll inf = 1e18;
    int n, n0;
    ll max_v[4*N], smax_v[4*N], max_c[4*N];
    ll min_v[4*N], smin_v[4*N], min_c[4*N];

    ll len[4*N];  // len[k]: ノードkの区間に含まれる要素数
    ll ladd[4*N]; // ladd[k]: RAQによって発生する、区間の a_i に加算するためのlazy tag

    ll sum_b[4*N]; // b_i の区間総和

    ll min_a[4*N]; // a_i が最小値の b_i に加算するlazy tag (区間chmaxクエリ用)
    ll max_a[4*N]; // a_i が最大値の b_i に加算するlazy tag (区間chminクエリ用)
    ll all_a[4*N]; // 区間内の b_i 全てに加算するlazy tag (区間加算クエリ用)

    void update_node_max(int k, ll x) {
      if(max_v[k] == min_v[k]) {
        max_v[k] = min_v[k] = x;
      } else if(max_v[k] == smin_v[k]) {
        max_v[k] = smin_v[k] = x;
      } else {
        max_v[k] = x;
      }
    }
    void update_node_min(int k, ll x) {
      if(max_v[k] == min_v[k]) {
        max_v[k] = min_v[k] = x;
      } else if(smax_v[k] == min_v[k]) {
        min_v[k] = smax_v[k] = x;
      } else {
        min_v[k] = x;
      }
    }

    // 親ノードpの最大値・最小値の状態を元に子ノードkの b_i の区間総和を更新
    // lazy valueの伝搬
    void add_b(int p, int k, ll mi, ll ma, ll aa) {
      // 親ノードpの最小値とノードkの最小値が等しい場合のみ更新と伝搬を行う
      if(p == -1 || min_v[p] == min_v[k]) {
        // S_B への加算
        sum_b[k] += mi * min_c[k];
        min_a[k] += mi;
      }

      // 親ノードpの最大値とノードkの最大値が等しい場合のみ更新と伝搬を行う
      if(p == -1 || max_v[p] == max_v[k]) {
        // S_A への加算
        sum_b[k] += ma * max_c[k];
        max_a[k] += ma;
      }

      // 全体(S_A + S_B + S_C)に加算する値の伝搬
      sum_b[k] += aa * len[k];
      all_a[k] += aa;
    }

    void addall(int k, ll x) {
      max_v[k] += x; smax_v[k] += x;
      min_v[k] += x; smin_v[k] += x;
      ladd[k] += x;
    }

    void push(int k) {
      if(ladd[k]) {
        addall(2*k+1, ladd[k]);
        addall(2*k+2, ladd[k]);
        ladd[k] = 0;
      }

      if(max_v[k] < max_v[2*k+1]) {
        update_node_max(2*k+1, max_v[k]);
      }
      if(min_v[2*k+1] < min_v[k]) {
        update_node_min(2*k+1, min_v[k]);
      }

      if(max_v[k] < max_v[2*k+2]) {
        update_node_max(2*k+2, max_v[k]);
      }
      if(min_v[2*k+2] < min_v[k]) {
        update_node_min(2*k+2, min_v[k]);
      }

      // 子ノードの最小値/最大値を更新した後に区間総和を更新
      if(min_a[k] != 0 || max_a[k] != 0 || all_a[k] != 0) {
        add_b(k, 2*k+1, min_a[k], max_a[k], all_a[k]);
        add_b(k, 2*k+2, min_a[k], max_a[k], all_a[k]);

        min_a[k] = max_a[k] = all_a[k] = 0;
      }
    }

    void update(int k) {
      // b_i の区間総和の値を子ノードから計算し直す
      sum_b[k] = sum_b[2*k+1] + sum_b[2*k+2];

      if(max_v[2*k+1] < max_v[2*k+2]) {
        max_v[k] = max_v[2*k+2];
        max_c[k] = max_c[2*k+2];
        smax_v[k] = max(max_v[2*k+1], smax_v[2*k+2]);
      } else if(max_v[2*k+1] > max_v[2*k+2]) {
        max_v[k] = max_v[2*k+1];
        max_c[k] = max_c[2*k+1];
        smax_v[k] = max(smax_v[2*k+1], max_v[2*k+2]);
      } else {
        max_v[k] = max_v[2*k+1];
        max_c[k] = max_c[2*k+1] + max_c[2*k+2];
        smax_v[k] = max(smax_v[2*k+1], smax_v[2*k+2]);
      }

      if(min_v[2*k+1] < min_v[2*k+2]) {
        min_v[k] = min_v[2*k+1];
        min_c[k] = min_c[2*k+1];
        smin_v[k] = min(smin_v[2*k+1], min_v[2*k+2]);
      } else if(min_v[2*k+1] > min_v[2*k+2]) {
        min_v[k] = min_v[2*k+2];
        min_c[k] = min_c[2*k+2];
        smin_v[k] = min(min_v[2*k+1], smin_v[2*k+2]);
      } else {
        min_v[k] = min_v[2*k+1];
        min_c[k] = min_c[2*k+1] + min_c[2*k+2];
        smin_v[k] = min(smin_v[2*k+1], smin_v[2*k+2]);
      }
    }

    void _update_min(ll x, int a, int b, int k, int l, int r) {
      if(b <= l || r <= a || max_v[k] <= x) {
        return;
      }
      if(a <= l && r <= b && smax_v[k] < x) {
        add_b(-1, k, 0, 1, 0);
        update_node_max(k, x);
        return;
      }

      push(k);
      _update_min(x, a, b, 2*k+1, l, (l+r)/2);
      _update_min(x, a, b, 2*k+2, (l+r)/2, r);
      update(k);
    }

    void _update_max(ll x, int a, int b, int k, int l, int r) {
      if(b <= l || r <= a || x <= min_v[k]) {
        return;
      }
      if(a <= l && r <= b && x < smin_v[k]) {
        add_b(-1, k, 1, 0, 0);
        update_node_min(k, x);
        return;
      }

      push(k);
      _update_max(x, a, b, 2*k+1, l, (l+r)/2);
      _update_max(x, a, b, 2*k+2, (l+r)/2, r);
      update(k);
    }

    void _add_val(ll x, int a, int b, int k, int l, int r) {
      if(b <= l || r <= a) {
        return;
      }
      if(a <= l && r <= b) {
        add_b(-1, k, 0, 0, 1);
        addall(k, x);
        return;
      }
      push(k);
      _add_val(x, a, b, 2*k+1, l, (l+r)/2);
      _add_val(x, a, b, 2*k+2, (l+r)/2, r);
      update(k);
    }

    ll _query_sum(int a, int b, int k, int l, int r) {
      if(b <= l || r <= a) {
        return 0;
      }
      if(a <= l && r <= b) {
        return sum_b[k];
      }
      push(k);
      ll lv = _query_sum(a, b, 2*k+1, l, (l+r)/2);
      ll rv = _query_sum(a, b, 2*k+2, (l+r)/2, r);
      return lv + rv;
    }

public:
  SegmentTree(int n, ll *a) : n(n) {
    n0 = 1;
    cout << 1 << endl;
    while(n0 < n) n0 <<= 1;

    len[0] = n0;
    for(int i=0; i<n0-1; ++i) len[2*i+1] = len[2*i+2] = (len[i] >> 1);
    for(int i=0; i<2*n0-1; ++i) {
      min_a[i] = max_a[i] = all_a[i] = 0;
      sum_b[i] = 0;
      ladd[i] = 0;
    }

    for(int i=0; i<n; ++i) {
      max_v[n0-1+i] = min_v[n0-1+i] = a[i];
      smax_v[n0-1+i] = -inf;
      smin_v[n0-1+i] = inf;
      max_c[n0-1+i] = min_c[n0-1+i] = 1;
    }
    for(int i=n; i<n0; ++i) {
      max_v[n0-1+i] = smax_v[n0-1+i] = -inf;
      min_v[n0-1+i] = smin_v[n0-1+i] = inf;
      max_c[n0-1+i] = min_c[n0-1+i] = 0;
    }
    for(int i=n0-2; i>=0; i--) update(i);
  }

  // 区間[a, b) について a_i の値を min(a_i, x) に更新
  void update_min(int a, int b, ll x) {
    return _update_min(x, a, b, 0, 0, n0);
  }

  // 区間[a, b) について a_i の値を max(a_i, x) に更新
  void update_max(int a, int b, ll x) {
    return _update_max(x, a, b, 0, 0, n0);
  }

  // 区間[a, b) について a_i の値を a_i+x に更新
  void add_val(int a, int b, ll x) {
    if(!x) return;
    _add_val(x, a, b, 0, 0, n0);
  }

  // 区間[a, b) の b_i の総和を求める
  ll query_sum(int a, int b) {
    return _query_sum(a, b, 0, 0, n0);
  }
};

int main() {
    int n, m; 
    cout << 1 << endl;
    cin >> n;
    ll *arr = new ll[n];
    for (int i=0; i<n; ++i) cin >> arr[i];
    cin >> m;
    SegmentTree tree(n, arr);
    // int op, l, r; ll x;
    // while (m--){
    //     cin >> op >> l >> r;
    //     if (op == 1){
    //         cin >> x;
    //         tree.add_val(l, r, x);
    //     } else if (op == 2){
    //         cin >> x;
    //         tree.update_max(l, r, x);
    //     } else if (op == 3){
    //         cin >> x;
    //         tree.update_min(l, r, x);
    //     } else {
    //         cout << tree.query_sum(l, r) << '\n';
    //     }
    // }
    // delete[] arr;
}