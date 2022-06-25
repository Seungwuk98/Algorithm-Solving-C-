#include <bits/stdc++.h>

using namespace std;


struct vec3
{
	int x, y, z;

	vec3(int x, int y, int z) : x(x), y(y), z(z) {}
	bool operator<(const vec3 &o) const {
		if (x ^ o.x) return x < o.x;
		if (y ^ o.y) return y < o.y;
		return z < o.z;
	}

	friend ostream& operator << (ostream &out, vec3 &v) {
		out << v.x << ' ' << v.y << ' ' << v.z;
		return out;
	}
};


int main()
{
	set<vec3> S;
	S.insert({1,2,3});
	S.insert({1,2,3});
	for (auto x : S) {
		cout << x << '\n';
	}
} // namespace std;
