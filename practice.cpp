#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define IDX(v, x) (lower_bound(all(v), x) - v.begin())
using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;
using Point = pair<ll, ll>;

istream& operator >> (istream &in, Point &t){ in >> t.x >> t.y; return in; }
Point operator + (Point p1, Point p2){ return {p1.x+p2.x, p1.y+p2.y}; }
Point operator - (Point p1, Point p2){ return {p1.x-p2.x, p1.y-p2.y}; }
ll    operator * (Point p1, Point p2){ return p1.x*p2.x + p1.y*p2.y; } /// dot product
ll    operator / (Point p1, Point p2){ return p1.x*p2.y - p2.x*p1.y; } /// cross product

ll _CCW(const Point &p1, const Point &p2, const Point &p3){ return (p2-p1)/(p3-p2); }
int CCW(Point p1, Point p2, Point p3){
    ll res = _CCW(p1, p2, p3);
    return (res > 0) - (res < 0);
}
ll D(const Point &p1, const Point &p2){
    ll dx = p1.x - p2.x, dy = p1.y - p2.y;
    return dx*dx + dy*dy;
}
inline double hypot(const Point p){ return hypot(p.x, p.y); }
inline Point Rot(const Point p){ return p.y >= 0 ? Point(p.y, -p.x) : Point(-p.y, p.x); }

int N, Idx[2020], Ord[2020];
Point A[2020];

struct Line{
    int i, j, flag; // -1: rot90
    Point s, e, dir;
    Line(int i, int j, int flag) : i(i), j(j), flag(flag), s(A[i]), e(A[j]) {
        if(s > e) swap(s, e);
        if(flag == 1) dir = e - s;
        else dir = Rot(e - s);
    }
    bool operator < (const Line &l) const {
        ll res = dir / l.dir; if(res) return res > 0;
        return tie(flag, s, e) < tie(l.flag, l.s, l.e);
    }
};

inline double solve_triangle(const Point &a, const Point &b, const Point &c){
    return abs(_CCW(a, b, c)) / hypot(a - b);
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> N; for(int i=1; i<=N; i++) cin >> A[i]; sort(A+1, A+N+1);
    for(int i=1; i<=N; i++) Ord[i] = Idx[i] = i;

    vector<Line> lines; lines.reserve(N*(N-1)/2);
    for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++) lines.emplace_back(i, j, 1), lines.emplace_back(i, j, -1);
    sort(all(lines));

    double mx = 0;
    for(const auto &line : lines){
        if(line.flag == 1){
            int a = line.i, b = line.j;
            swap(Idx[a], Idx[b]);
            swap(Ord[Idx[a]], Ord[Idx[b]]);
            a = Idx[line.i]; b = Idx[line.j]; if(a > b) swap(a, b);
            if(a-1 >= 1) mx = max(mx, solve_triangle(line.s, line.e, A[Ord[a-1]]));
            if(b+1 <= N) mx = max(mx, solve_triangle(line.s, line.e, A[Ord[b+1]]));
        }
        else{
            if(abs(Idx[line.i] - Idx[line.j]) == 1) mx = max(mx, hypot(A[line.i] - A[line.j]));
        }
    }
    cout << fixed << setprecision(10) << mx / 2 << "\n";
}