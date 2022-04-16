#include <iostream>
#include <math.h>

using namespace std;

double eps = 1e-6;
double INF = 3*(1e9);
double x,y,c;

double solve(double l){
    double a = sqrt(x*x-l*l);
    double b = sqrt(y*y-l*l);
    return a*b/(a+b);
}

double bisect(){
    double lo=0, hi = INF;
    while (fabs(hi-lo) > eps){
        double mid = (lo+hi)/2;
        if (solve(mid) < c) hi = mid;
        else lo = mid;
    }
    return lo;
}


int main()
{
    cin >> x >> y >> c;
    INF = min(x,y);
    cout << bisect() << '\n';
} // namespace std;
