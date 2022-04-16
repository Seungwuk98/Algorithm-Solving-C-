#include <iostream>

using namespace std;
class Vector
{
private:
    int x;
    int y;
    int z;

public:
    Vector() {}
    Vector(int x, int y, int z) : x(x), y(y), z(z) {}
    friend ostream &operator<<(ostream &os, const Vector &v)
    {
        os << v.x << " " << v.y << " " << v.z;
        return os;
    }

    friend istream &operator>>(istream &is, Vector &v)
    {
        string tmp;
        is >> tmp;
        v.x = stoi(tmp);
        is >> tmp;
        v.y = stoi(tmp);
        is >> tmp;
        v.z = stoi(tmp);

        return is;
    }

    Vector operator&(int a) const
    {
        return Vector{x & a, y & a, z & a};
    }

    Vector operator|(int a) const
    {
        return Vector{x | a, y | a, z | a};
    }

    Vector operator^(int a) const
    {
        return Vector(x ^ a, y ^ a, z ^ a);
    }

    Vector operator&(const Vector &v) const
    {
        return Vector{x & v.x, y & v.y, z & v.z};
    }

    Vector operator|(const Vector &v) const
    {
        return Vector{x | v.x, y | v.y, z | v.z};
    }

    Vector operator^(const Vector &v) const
    {
        return Vector(x ^ v.x, y ^ v.y, z ^ v.z);
    }

    Vector operator>>(int a) const
    {
        return Vector(x >> a, y >> a, z >> a);
    }

    Vector operator<<(int a) const
    {
        return Vector(x << a, y << a, z << a);
    }

    Vector operator~() const
    {
        return Vector(~x, ~y, ~z);
    }
};

int main()
{
    const Vector v(0, 0, 1);
    cout << v << endl;
    cout << ~v << endl;
    const Vector v1(1,1,1);
    cout << (v1^v) << endl;
    cout << (v1 >> 1) << endl;

} // namespace std;
