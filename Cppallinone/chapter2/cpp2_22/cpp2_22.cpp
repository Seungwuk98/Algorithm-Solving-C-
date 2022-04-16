#include <iostream>

using namespace std;
class Shape
{
public:
    virtual double getArea() const = 0; // 순수 가상함수->인터페이스
    virtual ~Shape() {}                 // 파괴자 중요
};

class Circle : public Shape
{
private:
    double _radius;

public:
    Circle(double radius) : _radius(radius) {}
    virtual double getArea() const
    {
        return _radius * _radius * 3.14;
    } // 순수 가상함수
};

class Rectangle : public Shape
{
private:
    double _width;
    double _height;

public:
    Rectangle(double width, double height) : _width(width), _height(height) {}

    virtual double getArea() const override
    {
        return _width * _height;
    }
};

class AreaAverage
{
private:
    double _total = 0;
    int _size = 0;

public:
    double operator()(Shape &shape)
    {
        _size++;
        _total += shape.getArea();
        return _total / _size;
    }
};

int main()
{
    Circle c(10);
    Rectangle r(10, 20);
    AreaAverage aavg;
    cout << aavg(c) << endl;
    cout << aavg(r) << endl;
} // namespace std;
