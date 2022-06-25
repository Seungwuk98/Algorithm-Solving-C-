#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

using ld = long double;
using ll = long long;
using pii = pair<int, int>;

struct vec3 {
    ld x, y, z;
    vec3(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}
    vec3 operator-(const vec3 &o) const {
        return vec3(x - o.x, y - o.y, z - o.z);
    }
    vec3 operator+(const vec3 &o) const {
        return vec3(x + o.x, y + o.y, z + o.z);
    }
    vec3 operator*(ld i) const {
        return vec3(x*i, y*i, z*i);
    }
    friend vec3 operator*(int i, const vec3 &o) {
        return vec3(i*o.x, i*o.y, i*o.z);
    }
    vec3 cross(const vec3 &o) const {
        return vec3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ld dot(const vec3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
    ld abs() const {
        return sqrt(dot(*this));
    }
    bool operator<(const vec3 &o) const {
        if (x != o.x) return x < o.x;
        if (y != o.y) return y < o.y;
        return z < o.z;
    }
    vec3 hat() {
        ld u = abs();
        return vec3(x/u, y/u, z/u);
    }
};

struct edge;

// The implementation becomes more challenging because we need information of adjacent faces.
// A face will have 3 edges for its adjacent faces
// e1 corresponds to the edge (a,b), e2 to (b,c), and e3 to (c,a)
// A face will store a list of future points that can see it.
// A face will also store "dead" - the index of the point responsible for deleting it (or 1e9 if alive)
struct face {
    int a, b, c;
    vec3 q;
    edge *e1, *e2, *e3;
    vector<int> points;
    int dead = 1e9;
    face(int a, int b, int c, vec3 q) : a(a), b(b), c(c), q(q) {
        e1 = e2 = e3 = NULL;
    }
};

// an edge will store the face it leads to and a pointer to the reverse edge
struct edge {
    edge *rev;
    face *f;
};

// This function will glue two faces together
// e1 is a reference to the F1 edge pointer, and e2 is a reference to the F2 edge pointer
void glue(face *F1, face *F2, edge* &e1, edge* &e2) {
    e1 = new edge;
    e2 = new edge;
    e1->rev = e2;
    e2->rev = e1;
    e1->f = F2;
    e2->f = F1;
};

// modify this to your liking
const ld EPS = 1e-9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// shuffles the point-set p, making sure the first 4 points are not coplanar.
// if all points are coplanar, an assertion fails
bool prepare(vector<vec3> &p) {
    int n = sz(p);
    shuffle(all(p), rng);
    vector<int> ve;
    ve.push_back(0);
    rep(i, 1, n) {
        if(sz(ve) == 1) {
            if((p[ve[0]] - p[i]).abs() > EPS) ve.push_back(i);
        }else if(sz(ve) == 2) {
            if((p[ve[1]] - p[ve[0]]).cross(p[i] - p[ve[0]]).abs() > EPS) ve.push_back(i);
        }else if(abs((p[i] - p[ve[0]]).dot((p[ve[1]] - p[ve[0]]).cross(p[ve[2]] - p[ve[0]]))) > EPS) {
            ve.push_back(i);
            break;
        }
    }
    if (sz(ve) != 4) return false;
    vector<vec3> ve2;
    for(int i : ve) ve2.push_back(p[i]);
    reverse(all(ve));
    for(int i : ve) p.erase(p.begin() + i);
    p.insert(p.begin(), all(ve2));
    return true;
}

vector<face*> hull3(vector<vec3> &p) {
    int n = sz(p);
    bool chk = prepare(p);
    vector<face*> f, new_face(n, NULL);
    if (!chk) return f;
    vector<vector<face*>> conflict(n);
    auto add_face = [&](int a, int b, int c) {
        face *F = new face(a, b, c, (p[b] - p[a]).cross(p[c] - p[a]));
        f.push_back(F);
        return F;
    };

    face *F1 = add_face(0, 1, 2);
    face *F2 = add_face(0, 2, 1);
    glue(F1, F2, F1->e1, F2->e3);
    glue(F1, F2, F1->e2, F2->e2);
    glue(F1, F2, F1->e3, F2->e1);
    rep(i, 3, n) {
        for(face *F : {F1, F2}) {
            ld Q = (p[i] - p[F->a]).dot(F->q);
            if(Q > EPS) conflict[i].push_back(F);
            if(Q >= -EPS) F->points.push_back(i);
        }
    }

    rep(i, 3, n) {
        for(face *F : conflict[i]) F->dead = min(F->dead, i);
        int v = -1;
        for(face *F : conflict[i]) {
            if(F->dead != i) continue;
            int parr[3] = {F->a, F->b, F->c};
            edge* earr[3] = {F->e1, F->e2, F->e3};
            rep(j, 0, 3) {
                int j2 = (j + 1);
                if(j2 >= 3) j2 -= 3;

                if(earr[j]->f->dead > i) {
                    face *Fn = new_face[parr[j]] = add_face(parr[j], parr[j2], i);
                    set_union(all(F->points), all(earr[j]->f->points), back_inserter(Fn->points));
                    Fn->points.erase(stable_partition(all(Fn->points), [&](int k) {
                        return k > i && (p[k] - p[Fn->a]).dot(Fn->q) > EPS;
                    }), Fn->points.end());
                    for(int k : Fn->points) {
                        conflict[k].push_back(Fn);
                    }
                    earr[j]->rev->f = Fn;
                    Fn->e1 = earr[j];
                    v = parr[j];
                }
            }
        }
        if(v == -1) continue;

        while(new_face[v]->e2 == NULL) {
            int u = new_face[v]->b;
            glue(new_face[v], new_face[u], new_face[v]->e2, new_face[u]->e3);
            v = u;
        }
    }

    // Remove dead faces
    f.erase(remove_if(all(f), [&](face *F) {
        return F->dead < n;
    }), f.end());
    return f;
}


struct vec2
{
    ld x, y;
    vec2(){}
    vec2(ld x, ld y) : x(x), y(y) {}
} ;

struct convex_hull
{
    vec2 p0;
    int n;
    vector<vec2> hull;
    ld ccw(const vec2 &p1, const vec2 &p2, const vec2 &p3) {
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
            ld v = ccw(p0, p1, p2);
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

struct plane;
vec3 intersect_plane(plane &pl, vec3 f, vec3 dir);

struct plane
{
    vec3 norm;
    ld d;
    plane(ld a, ld b, ld c, ld d) : d(d) {
        norm = vec3(a, b, c);
    }
    ld val(vec3 &v) {
        return norm.dot(v) + d;
    }
    tuple<vec3, vec3, vec3> coord() {
        vec3 O(0,0,0);
        if (d != 0) {
            O = intersect_plane(*this, vec3(0,0,0), norm);
        }
        vec3 never(2103, 1, 0);
        vec3 xh = norm.cross(never);
        vec3 yh = norm.cross(xh);
        return {xh.hat(), yh.hat(), O};
    }
};


vec3 intersect_plane(plane &pl, vec3 f, vec3 dir) {
    ld t = -(pl.norm.dot(f) + pl.d) / (pl.norm.dot(dir));
    return f + dir*t;
}

set<vec3> intersect_all(plane &pl, vector<face*> &f, vector<vec3> &P) {
    set<vec3> ret;
    for (vec3 &v : P) {
        if (pl.val(v) == 0) ret.insert(v);
    }
    for (face *u : f) {
        int a = u->a, b = u->b, c = u->c;
        vec3 &A = P[a], &B = P[b], &C = P[c];
        ld plA = pl.val(A); ld plB = pl.val(B); ld plC = pl.val(C);
        if (plA == 0) ret.insert(A);
        if (plB == 0) ret.insert(B);
        if (plC == 0) ret.insert(C);
        if (plA * plB < 0) ret.insert(intersect_plane(pl, A, B-A));
        if (plB * plC < 0) ret.insert(intersect_plane(pl, B, C-B));
        if (plC * plA < 0) ret.insert(intersect_plane(pl, C, A-C));
    }
    return ret;
}

vector<vec2> convert(set<vec3> &P, plane &pl) {
    auto [xh, yh, O] = pl.coord();
    vector<vec2> ret;
    for (vec3 p : P) {
        ld x = xh.dot(p-O);
        ld y = yh.dot(p-O);
        ret.push_back({x, y});
    }
    return ret;
}

int main(){
    int n, q;
    fastio
    cin >> n >> q;
    vector<vec3> P;
    for (int i=0; i<n; ++i) {
        ld x, y, z; cin >> x >> y >> z;
        P.push_back({x, y, z});
    }

    
    vector<face *> hull = hull3(P);
    
    while (q--) {
        ld a, b, c, d; cin >> a >> b >> c >> d;
        plane pl(a, b, c, d);
        set<vec3> inter = intersect_all(pl, hull, P);
        if (inter.size() < 3) {
            cout << "0\n";
            continue;
        }
        vector<vec2> conv = convert(inter, pl);
        convex_hull ans(conv);
        cout.precision(8);
        cout << fixed << ans.area() << '\n';
    }

}