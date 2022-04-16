#include <iostream>

using namespace std;

class Vector
{
public:
    float x, y, z;

    Vector(int x, int y, int z) : x(x), y(y), z(z) {}

    float &operator[](int idx)
    {
        if (!idx)
            return x;
        if (idx == 1)
            return y;
        if (idx == 2)
            return z;
    }
    const float& operator[](int idx) const
    {
        if (!idx)
            return x;
        if (idx == 1)
            return y;
        if (idx == 2)
            return z;
    }
};

int main()
{
    Vector v{1, 2, 3};
    cout << v[0] << endl;
    cout << v[1] << endl;
    cout << v[2] << endl;

    v[0] = 10;
    cout << v[0] << endl;

    const Vector v1{2,3,4};
    cout << v[0] << endl;
} // namespace std;
