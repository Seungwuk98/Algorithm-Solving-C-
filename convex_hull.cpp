#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
using ld = long double;
struct vec2
{
    ll x, y;
    vec2(){}
    vec2(ll x, ll y) : x(x), y(y) {}
} ;

struct convex_hull
{
    vec2 p0;
    int n;
    vector<vec2> hull;
    ll ccw(const vec2 &p1, const vec2 &p2, const vec2 &p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    }


    convex_hull(vector<vec2> &pts) {
        n = pts.size();
        int mn = 0;
        for (int i=0; i<n; ++i) {
            if (pts[mn].x > pts[i].x) mn = i;
            else if (pts[mn].x == pts[i].x && pts[mn].y > pts[i].y) mn = i;
        }
        p0 = pts[mn];
        pts.erase(pts.begin()+mn);

        auto angle_comp = [&](const vec2 &p1, const vec2 &p2) {
            ll v = ccw(p0, p1, p2);
            if (v != 0) return v > 0;
            else {
                if (p1.x != p2.x) return p1.x < p2.x;
                return p1.y < p2.y;
            }
        };
        sort(all(pts), angle_comp);
        hull.push_back(p0);
        for (int i=0; i<n-1; ++i) {
            while (hull.size() >= 2 && ccw(*(hull.end()-2), *(hull.end()-1), pts[i]) <= 0) hull.pop_back();
            hull.push_back(pts[i]);
        }
        if (ccw(*(hull.end()-2), *(hull.end()-1), p0) == 0) hull.pop_back();
    }

    ld area(){
        ld ret = 0;
        for (int i=1; i<hull.size()-1; ++i) {
            ret += (ld)ccw(p0, hull[i], hull[i+1])/2;
        }
        return ret;
    }
};

int main()
{
    int n; cin >> n;
    vector<vec2> pts(n);
    for (int i=0; i<n; ++i){
        cin >> pts[i].x >> pts[i].y;
    }

    convex_hull ret(pts);
    cout << ret.hull.size() << endl;
    // cout << ret.area();
} // namespace std
