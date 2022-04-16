#include <iostream>

using namespace std;

class Vector
{

private:
    float x;
    float y;
    float z;

public:
    Vector(float x, float y, float z) : x(x), y(y), z(z){};
    Vector operator+() const
    {
        return *this;
    }

    Vector operator-() const
    {
        return Vector{-x, -y, -z};
    }

    Vector operator+(const Vector &v) const
    {
        return Vector{x + v.x, y + v.y, z + v.z};
    }

    Vector operator-(const Vector &v) const
    {
        return Vector{x - v.x, y - v.y, z - v.z};
    }

    float operator*(const Vector &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector operator*(float a) const
    {
        return Vector{x * a, y * a, z * a};
    }

    Vector operator/(float a) const
    {
        return Vector{x / a, y / a, z / a};
    }

    Vector &operator++()
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }
    Vector &operator--()
    {
        --x;
        --y;
        --z;
        return *this;
    }

    Vector &operator++(int)
    {
        Vector tmp = *this;
        ++(*this);
        return tmp;
    }
    Vector &operator--(int)
    {
        Vector tmp = *this;
        --(*this);
        return tmp;
    }

    friend Vector operator*(float v0, const Vector &v1);

    void print() const
    {
        cout << "x : " << x << " y : " << y << " z : " << z << endl;
    }
};

Vector operator*(float v0, const Vector &v1)
{
    return Vector{v0 * v1.x, v0 * v1.y, v0 * v1.z};
}

int main()
{
    Vector v0{0, 1, 2};
    Vector v1{1, 2, 3};

    v0.print();
    v1.print();

    Vector v2 = v0 + v1; // Vector v2 = v0.operator+(v1);
    Vector v3 = -v1;     // Vector v3 = v1.operator-();
    Vector v4 = +v1;
    Vector v5 = v1 * 5;

    v2.print();
    v3.print();
    v4.print();
    v5.print();

    v0++;
    v0.print();
    v0--;
    v0.print();
    --v0;
    v0.print();
    ++v0;
    v0.print();

    Vector v6 = 5.0f * v1;
    v6.print();

    // 단항 연산자 + +vector = vector
    // 이항 연산자 - vector - vector = vector
    // 이항 연산자 *, vector o vector = float,  vector * 3.0f = vector
    // 이항 연산자 /, vector / 3.0f = vector
    // 전위 연산자 ++ --, ++vector, -- vector
    // 후위 연산자 ++ --, vector++, vector--

} // namespace std;
