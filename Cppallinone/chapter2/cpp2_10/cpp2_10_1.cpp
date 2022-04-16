#include <iostream>

using namespace std;

class VectorI
{
    friend class VectorF;

private:
    int x;
    int y;
    int z;

public:
    VectorI(int x, int y, int z) : x(x), y(y), z(z){};
    VectorI operator+() const
    {
        return *this;
    }

    VectorI operator-() const
    {
        return VectorI{-x, -y, -z};
    }

    VectorI operator+(const VectorI &v) const
    {
        return VectorI{x + v.x, y + v.y, z + v.z};
    }

    VectorI operator-(const VectorI &v) const
    {
        return VectorI{x - v.x, y - v.y, z - v.z};
    }

    float operator*(const VectorI &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    VectorI operator*(float a) const
    {
        return VectorI{x * a, y * a, z * a};
    }

    VectorI operator/(float a) const
    {
        return VectorI{x / a, y / a, z / a};
    }

    VectorI &operator++()
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }
    VectorI &operator--()
    {
        --x;
        --y;
        --z;
        return *this;
    }

    VectorI &operator++(int)
    {
        VectorI tmp = *this;
        ++(*this);
        return tmp;
    }
    VectorI &operator--(int)
    {
        VectorI tmp = *this;
        --(*this);
        return tmp;
    }

    void print() const
    {
        cout << "x : " << x << " y : " << y << " z : " << z << endl;
    }
};
class VectorF
{

private:
    float x;
    float y;
    float z;

public:
    VectorF(float x, float y, float z) : x(x), y(y), z(z){};
    VectorF operator+() const
    {
        return *this;
    }

    VectorF operator-() const
    {
        return VectorF{-x, -y, -z};
    }

    VectorF operator+(const VectorF &v) const
    {
        return VectorF{x + v.x, y + v.y, z + v.z};
    }

    VectorF operator-(const VectorF &v) const
    {
        return VectorF{x - v.x, y - v.y, z - v.z};
    }

    float operator*(const VectorF &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    VectorF operator*(float a) const
    {
        return VectorF{x * a, y * a, z * a};
    }

    VectorF operator/(float a) const
    {
        return VectorF{x / a, y / a, z / a};
    }

    VectorF &operator++()
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }
    VectorF &operator--()
    {
        --x;
        --y;
        --z;
        return *this;
    }

    VectorF &operator++(int)
    {
        VectorF tmp = *this;
        ++(*this);
        return tmp;
    }
    VectorF &operator--(int)
    {
        VectorF tmp = *this;
        --(*this);
        return tmp;
    }

    friend VectorF operator*(float v0, const VectorF &v1);

    void print() const
    {
        cout << "x : " << x << " y : " << y << " z : " << z << endl;
    }
};

VectorF operator*(float v0, const VectorF &v1)
{
    return VectorF{v0 * v1.x, v0 * v1.y, v0 * v1.z};
}

int main()
{

    // 단항 연산자 + +vector = vector
    // 이항 연산자 - vector - vector = vector
    // 이항 연산자 *, vector o vector = float,  vector * 3.0f = vector
    // 이항 연산자 /, vector / 3.0f = vector
    // 전위 연산자 ++ --, ++vector, -- vector
    // 후위 연산자 ++ --, vector++, vector--

} // namespace std;
