#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

struct Print
{
public:
    void operator()(int v) const
    {
        cout << v << endl;
    }
};

class Max
{
private:
    int _max = numeric_limits<int>::min();

public:
    int operator()(int x)
    {
        return _max = max(x, _max);
    }
};

struct Average
{
private:
    double _total = 0;
    int _times = 0;

public:
    double operator()(double value)
    {
        _times++;
        _total += value;
        return _total / _times;
    }
};

int main()
{
    Max mx;
    cout << mx(1) << endl;
    cout << mx(3) << endl;
    cout << mx(6) << endl;
    cout << mx(12) << endl;
    cout << mx(2) << endl;

    Average avg;
    cout << avg(100) << endl;
    cout << avg(200) << endl;
    cout << avg(300) << endl;

    Print p;
    int num[] = {1, 2, 3, 4, 5};
    for (int x : num)
    {
        p(x);
    }

    std::for_each(num, num + size(num), Print());
    function<void(int)> f = p;
    f(10);

    plus<int> s;
    cout << s(1,2) << endl;

    negate<int> n;
    cout << n(1) << endl;

    equal_to<int> et;
    cout << et(1,1) << endl;

} // namespace std;
