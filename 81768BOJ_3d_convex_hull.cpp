#include <bits/stdc++.h>
#define PI 3.14159265358979323846264338327950288419716939937510L
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define vi vector<int>
#define pii pair<int, int>
#define rep(i, a, b) for(int i = (a); i < (b); i++)

using namespace std;

using ld = long double;
const ld EPS = 1e-9;


struct vec3 {
    ld x, y, z;
    vec3(ld x = 0, ld y = 0, ld z = 0) : x(x), y(y), z(z) {}
    vec3 operator-(const vec3 &o) const {
        return vec3(x - o.x, y - o.y, z - o.z);
    }
    ld operator*(const vec3 &o) const {
        return x*o.x + y*o.y + z*o.z;
    }
    vec3 cross(const vec3 &o) const {
        return vec3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ld& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        return z;
    }
    ld dot(const vec3 &o) const {
        return x * o.x + y * o.y + z * o.z;
    }
    ld abs() const {
        return sqrt(dot(*this));
    }
    ld operator~() const {
        return abs();
    }
};

struct edge;

struct face {
    int a, b, c;
    vec3 q;
    edge *e1, *e2, *e3;
    vi points;
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


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// shuffles the point-set p, making sure the first 4 points are not coplanar.
// if all points are coplanar, an assertion fails
void prepare(vector<vec3> &p) {
    int n = sz(p);
    shuffle(all(p), rng);
    vi ve;
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
    assert(sz(ve) == 4);
    vector<vec3> ve2;
    for(int i : ve) ve2.push_back(p[i]);
    reverse(all(ve));
    for(int i : ve) p.erase(p.begin() + i);
    p.insert(p.begin(), all(ve2));
}

vector<face*> hull3(vector<vec3> &p) {
    int n = sz(p);
    prepare(p);
    vector<face*> f, new_face(n, NULL);

    // for a point i, conflict[i] is the list of faces it can see.
    // It might contain faces that were deleted, and we should ignore them
    vector<vector<face*>> conflict(n);
    auto add_face = [&](int a, int b, int c) {
        face *F = new face(a, b, c, (p[b] - p[a]).cross(p[c] - p[a]));
        f.push_back(F);
        return F;
    };

    // initialize a triangular disk of the first 3 points.
    // The initial tetrahedron is handled automatically when we insert the 4th point
    face *F1 = add_face(0, 1, 2);
    face *F2 = add_face(0, 2, 1);
    glue(F1, F2, F1->e1, F2->e3);
    glue(F1, F2, F1->e2, F2->e2);
    glue(F1, F2, F1->e3, F2->e1);
    rep(i, 3, n) {
        for(face *F : {F1, F2}) {
            ld Q = (p[i] - p[F->a]).dot(F->q);
            if(Q > EPS) conflict[i].push_back(F);
            // making this second check is an ugly consequence of starting with a degenerate triangular disk.
            // We want to make sure each future point is considered visible to some initial face.
            if(Q >= -EPS) F->points.push_back(i);
        }
    }

    rep(i, 3, n) {
        // mark all visible faces as dead
        for(face *F : conflict[i]) F->dead = min(F->dead, i);

        // If a dead face and alive face are adjacent, we have an exposed edge
        // Vertex v will be a vertex on some exposed edge
        int v = -1;
        for(face *F : conflict[i]) {
            if(F->dead != i) continue;
            int parr[3] = {F->a, F->b, F->c};
            edge* earr[3] = {F->e1, F->e2, F->e3};
            rep(j, 0, 3) {
                int j2 = (j + 1);
                if(j2 >= 3) j2 -= 3;

                if(earr[j]->f->dead > i) {
                    // F is dead and earr[j]->f is alive.
                    // We should add a new face Fn, attach it to earr[j]->f,
                    // combine the point lists of the two faces into Fn,
                    // and store Fn in new_face[parr[j]] so we can glue all the new faces together in a cone.
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
        // There are no exposed edges
        if(v == -1) continue;

        // Glue all the new cone faces together
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
    friend ostream& operator << (ostream &out, const vec2 &v) {
        out << v.x << ' ' << v.y;
        return out;
    }
};


struct matrix
{
    ld table[3][3] = {0,};
    matrix() {
    }
    matrix(ld mat[][3]) {
        for (int i=0; i<3; ++i) for (int j=0; j<3; ++j) table[i][j] = mat[i][j];
    }
    vec3 operator* (vec3 &v) {
        vec3 ret;
        for (int i=0; i<3; ++i) for (int j=0; j<3; ++j) ret[i] += table[i][j] * v[j];
        return ret;
    }

    matrix operator* (const matrix &m) const {
        matrix ret;
        for (int i=0; i<3; ++i) for (int j=0; j<3; ++j) for (int k=0; k<3; ++k) {
            ret.table[i][j] += table[i][k] * m.table[k][j];
        }
        return ret;
    }
    friend ostream& operator << (ostream &out, const matrix &m) {
        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) out << m.table[i][j] << ' ';
            out << endl;
        } 
        return out;
    }
};



ld get_angle(vec3 hat, vec3 &p) {
    return acos((hat * p)/((~hat) * (~p)));
}

ld get_theta(vec3 hat, vec3 &p) {
    ld theta = get_angle(hat, p);
    return p.y < 0 ? PI-theta : theta;
}

matrix rotate_matrix(vec3 v) {
    if (v.x == 0 && v.y == 0) {
        matrix ret;
        ret.table[0][0] = ret.table[1][1] = ret.table[2][2] = 1;
        return ret;
    }
    vec3 xy(v.x, v.y, 0);
    ld theta = get_theta(vec3(1,0,0), xy);
    ld mat_xy[3][3] = {
        {cosl(theta), sinl(theta), 0L},
        {-sinl(theta), cosl(theta), 0L},
        {0, 0, 1}
    };
    ld phi = get_angle(vec3(0,0,1), v);
    ld mat_y[3][3] = {
        {cosl(phi), 0, -sinl(phi)},
        {0, 1, 0},
        {sinl(phi), 0, cosl(phi)}
    };
    return matrix(mat_y) * matrix(mat_xy);
}

struct plane {
    ld a,b,c,d;
    vec3 normal;
    plane(ld a, ld b, ld c, ld d) : a(a), b(b), c(c), d(d) {
        normal = vec3(a,b,c);
    }
};

struct line
{
    vec3 point, dir;
    line(vec3 p, vec3 dir) : point(p), dir(dir) {}
};


vec3 intersection_point(const plane &p, const line &l){
    vec3 nl = p.normal;
    ld t = -(p.d + nl * l.point) / (nl * l.dir);
    return vec3(l.point.x + l.dir.x * t, l.point.y + l.dir.y * t, l.point.z + l.dir.z * t);
}

vector<vec3> intersection_points(const plane &p, const face &f, vector<vec3> &pts) {
    auto plane_value = [&](vec3 &A) {
        return p.normal * A + p.d;
    };
    ld vA = plane_value(pts[f.a]);
    ld vB = plane_value(pts[f.b]);
    ld vC = plane_value(pts[f.c]);
    vector<vec3> ret;
    if (vA * vB < 0) {
        ret.push_back(intersection_point(p, line(pts[f.a], pts[f.a]-pts[f.b])));
    }
    if (vB * vC < 0) {
        ret.push_back(intersection_point(p, line(pts[f.b], pts[f.b]-pts[f.c])));
    }
    if (vC * vA < 0) {
        ret.push_back(intersection_point(p, line(pts[f.c], pts[f.c]-pts[f.a])));
    }
    return ret;
}

vector<vec3> all_inter_points(const plane &p, vector<face*> &hull, vector<vec3> &pts) {
    vector<vec3> ret;
    auto plane_value = [&](vec3 &A) {
        return p.normal * A + p.d;
    };
    for (auto pt : pts) {
        if (abs(plane_value(pt)) < EPS) ret.push_back(pt);
    }
    for (auto f : hull) {
        vector<vec3> tmp = intersection_points(p, *f, pts);
        ret.insert(ret.end(), all(tmp));
    }
    return ret;
}

vector<vec2> rotate_all_points(const plane &p, vector<vec3> &points) {
    matrix RM = rotate_matrix(p.normal);
    vector<vec2> ret;
    for (int i=0; i<points.size(); ++i) {
        points[i].z -= p.d;
        points[i] = RM * points[i];
        ret.emplace_back(points[i].x, points[i].y);
    }
    return ret;
}



struct hull2
{
    vec2 p0;
    int n;
    vector<vec2> hull;
    ld ccw(const vec2 &p1, const vec2 &p2, const vec2 &p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    }


    hull2(vector<vec2> &pts) {
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
            ret += ccw(p0, hull[i], hull[i+1])/2;
        }
        return ret;
    }
};


int main()
{
    fastio
    int n,m; cin >> n >> m;
    vector<vec3> pts;
    for (int i=0; i<n; ++i) {
        ld x,y,z; cin >> x >> y >> z;
        pts.emplace_back(x,y,z);
    }
    vector<face*> hull = hull3(pts);
    while (m--) {
        ld a,b,c,d;
        cin >> a >> b >> c >> d;
        if (n>=3) {
            plane p(a,b,c,d);
            vector<vec3> aip = all_inter_points(p, hull, pts);
            if (aip.size() < 3) {
                cout << 0 << '\n';
                continue;
            }
            vector<vec2> rtdp = rotate_all_points(p, aip);
            hull2 h2(rtdp);
            cout << fixed << setprecision(10) << h2.area() << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
} // namespace std;
