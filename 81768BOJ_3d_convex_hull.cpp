#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define PI 3.14159265358979323846264338327950288419716939937510L
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

using ld = long double;
const ld EPS = 1e-9;

struct vec3
{
    ld x, y, z;
    vec3(){x=y=z=0;}
    vec3(ld x, ld y, ld z) : x(x), y(y), z(z) {}
    vec3 operator-(const vec3 &o) const {
        return vec3(x - o.x, y - o.y, z - o.z);
    }
    vec3 operator/(const vec3 &o) const {
        return vec3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
    }
    ld operator*(const vec3 &o) const {
        return x*o.x + y*o.y + z*o.z;
    }
    ld& operator[](int i) {
        if (i == 0) return x;
        if (i == 1) return y;
        if (i == 2) return z;
        return z;
    }
    ld operator~() {
        return sqrt(x*x + y*y + z*z);
    }

    friend ostream& operator << (ostream &out, const vec3 &v) {
        out << v.x << ' ' << v.y << ' ' << v.z;
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



// ld get_angle(vec3 hat, vec3 &p) {
//     return acos((hat * p)/((~hat) * (~p)));
// }

// ld get_theta(vec3 hat, vec3 &p) {
//     ld theta = get_angle(hat, p);
//     return p.y < 0 ? PI-theta : theta;
// }

// matrix rotate_matrix(vec3 v) {
//     if (v.x == 0 && v.y == 0) {
//         matrix ret;
//         ret.table[0][0] = ret.table[1][1] = ret.table[2][2] = 1;
//         return ret;
//     }
//     vec3 xy(v.x, v.y, 0);
//     ld theta = get_theta(vec3(1,0,0), xy);
//     ld mat_xy[3][3] = {
//         {cosl(theta), sinl(theta), 0L},
//         {-sinl(theta), cosl(theta), 0L},
//         {0, 0, 1}
//     };
//     ld phi = get_angle(vec3(0,0,1), v);
//     ld mat_y[3][3] = {
//         {cosl(phi), 0, -sinl(phi)},
//         {0, 1, 0},
//         {sinl(phi), 0, cosl(phi)}
//     };
//     return matrix(mat_y) * matrix(mat_xy);
// }

struct face
{
    int a, b, c;
    vec3 q;
};

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
    if (vA * vB <= 0) {
        ret.push_back(intersection_point(p, line(pts[f.a], pts[f.a]-pts[f.b])));
    }
    if (vB * vC <= 0) {
        ret.push_back(intersection_point(p, line(pts[f.b], pts[f.b]-pts[f.c])));
    }
    if (vC * vA <= 0) {
        ret.push_back(intersection_point(p, line(pts[f.c], pts[f.c]-pts[f.a])));
    }
    return ret;
}

vector<vec3> all_inter_points(const plane &p, vector<face> &hull, vector<vec3> &pts) {
    vector<vec3> ret;
    auto plane_value = [&](vec3 &A) {
        return p.normal * A + p.d;
    };
    for (auto f : hull) {
        vector<vec3> tmp = intersection_points(p, f, pts);
        ret.insert(ret.end(), all(tmp));
    }
    return ret;
}

// vector<vec2> rotate_all_points(const plane &p, vector<vec3> &points) {
//     matrix RM = rotate_matrix(p.normal);
//     vector<vec2> ret;
//     for (int i=0; i<points.size(); ++i) {
//         points[i].z -= p.d;
//         points[i] = RM * points[i];
//         ret.emplace_back(points[i].x, points[i].y);
//     }
//     return ret;
// }


vector<face> hull3(const vector<vec3> &p) {
    int n = p.size();
    if (n<3) {
        return vector<face>();
    }
    vector<face> f;

    vector<vector<bool>> dead(n, vector<bool>(n, true));
    auto add_face = [&](int a, int b, int c) {
        f.push_back({a, b, c, (p[b]-p[a])/(p[c]-p[a])});
        dead[a][b] = dead[b][c] = dead[c][a] = false;
    };
    add_face(0, 1, 2);
    add_face(0, 2, 1);
    for (int i=3; i<n; ++i) {
        vector<face> f2;
        for (face &F : f) {
            if ((p[i] - p[F.a])*F.q > EPS) {
                dead[F.a][F.b] = dead[F.b][F.c] = dead[F.c][F.a] = true;
            } else {
                f2.push_back(F);
            }
        }
        f.clear();
        for (face &F : f2) {
            int arr[3] = {F.a, F.b, F.c};
            for (int j=0; j<3; ++j) {
                int a = arr[j], b = arr[(j+1)%3];
                if (dead[b][a]) add_face(b,a,i);
            }
        }
        f.insert(f.end(), all(f2));
    }
    return f;
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
    vector<face> hull = hull3(pts);
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
