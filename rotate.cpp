#include <bits/stdc++.h>
#define PI 3.14159265358979323846264338327950288419716939937510L

using namespace std;
using ld = long double;

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



ld get_angle(vec3 hat, vec3 p) {
    return acos((hat * p)/((~hat) * (~p)));
}

matrix rotate_matrix(vec3 v) {
    vec3 xy(v.x, v.y, 0);
    ld theta = get_angle(vec3(1,0,0), xy);
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

int main()
{
    ld mat[3][3] = {
        {1, 2, 3},
        {1, 2, 1},
        {3, 3, 1}
    };
    matrix x(mat);
    vec3 v(124,352355,2342);
    cout << x * v << endl;
    cout << rotate_matrix(v) * v << endl;
} // namespace std;
