#include <iostream>

using namespace std;

class Length
{

private:
    const long double _value;
    Length(long double value) : _value(value) {}

    friend Length operator"" _m(unsigned long long int value);
    friend Length operator"" _m(long double value);
    friend Length operator"" _km(unsigned long long int value);
    friend Length operator"" _km(long double value);
    friend Length operator"" _cm(unsigned long long int value);
    friend Length operator"" _cm(long double value);
    friend Length operator"" _mm(unsigned long long int value);
    friend Length operator"" _mm(long double value);

public:
    long double m() const { return _value; }
    long double km() const { return _value * 0.001L; }
    long double cm() const { return _value * 100.0L; }
    long double mm() const { return _value * 1000.0L; }

    Length operator-() const
    {
        return Length(-_value);
    }
    Length operator+() const
    {
        return Length(_value);
    }
    Length operator+(const Length &length) const
    {
        return Length(_value + length._value);
    }
    Length operator-(const Length &length) const
    {
        return Length(_value - length._value);
    }
};

Length operator"" _m(unsigned long long int value)
{
    return Length(value);
}
Length operator"" _m(long double value)
{
    return Length(value);
}
Length operator"" _km(unsigned long long int value)
{
    return Length(value * 1000L);
}
Length operator"" _km(long double value)
{
    return Length(value * 1000L);
}
Length operator"" _cm(unsigned long long int value)
{
    return Length(value * 0.01L);
}
Length operator"" _cm(long double value)
{
    return Length(value * 0.01L);
}
Length operator"" _mm(unsigned long long int value)
{
    return Length(value * 0.001L);
}
Length operator"" _mm(long double value)
{
    return Length(value * 0.001L);
}

int main()
{
    Length l = 1_m + 1_km + 1_cm - 1_mm;
    cout.precision(16);
    cout << l.m() << endl;
    cout << l.km() << endl;
} // namespace std;
