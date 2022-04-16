#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using ld = long double;
ld eps = 0.000000001;
ld eps2 = 0.00000000001l;
ld a,b,c,d;
ld A,B,C;
int INF = 1000000;

ld f(ld x){
    return a*x*x*x+b*x*x+c*x+d;
}

ld det(ld a, ld b, ld c){
    return b*b-4*a*c;
}


int main()
{
    int N;
    cin >> N;
    while (N--){
        cin >> a >> b >> c >> d;
        int r; ld mfi = 1e40;
        for (int i=-INF;i<=INF;i++){
            ld fi= f(i);
            if (fabsl(fi) < mfi){
                mfi = fabsl(fi);
                r = i;
            }
        }
        A = a;
        B = b+A*r;
        C = c+B*r;
        ld D = det(A,B,C);
        set<ld> s;
        if (D<0) s.insert(r);
        else {
            ld x1 = (-B+sqrt(D))/(2*A)
            ld x2 = (-B-sqrt(D))/(2*A)
            if (fabs(x1-x2) <= eps && fabs(x1-r) <= eps && fabs(x2-r) <=eps) s.insert(r);
            else if (fabs(x1-x2) > eps){
            }
        }
        for (auto i=s.begin(); i!=s.end(); i++) printf("%.10Lf ", *i);
        cout << '\n';


    }


} // namespace std;
