#include <bits/stdc++.h>

using namespace std;
using ld = long double; 

struct vec3
{
    ld x, y, z;
    vec3 operator* (ld M) {
        return {x*M, y*M, z*M};
    }
    ld operator* (vec3 &o) const {
        return x*o.x + y*o.y + z*o.z;
    }
    ld abs() {
        return (*this)*(*this);
    }
    vec3 operator+ (vec3 &o) const {
        return {x+o.x, y+o.y, z+o.z};
    }
    vec3 operator- (vec3 &o) const {
        return {x-o.x, y-o.y, z-o.z};
    }
};

ld bisect(vec3 &A, vec3 &B, vec3 &C) {
    ld lo = 0, hi = 1;
    while (abs(hi - lo) > 1e-9) {
        
    }
}

int main()
{
    
} // namespace std;
