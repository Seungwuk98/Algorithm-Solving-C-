#include <math.h>
#include <complex>
#include <vector>

using namespace std;

const double PI = acos(-1); // PI 값을 지정해 놓음
typedef complex<double> cpx;
 
// n-1차 다항식 f를 n개의 복소수로 DFT함. 이때 x = w
void FFT(vector<cpx> &f, cpx w){
    int n = f.size();
    if(n == 1) return; // base case
 
    // 다항식 분리
    vector<cpx> even(n/2), odd(n/2);
    for(int i = 0; i < n; ++i)
        (i%2 ? odd : even)[i/2] = f[i];
 
    // divide: 각각의 다항식을 재귀적으로 DFT함
    FFT(even, w*w);
    FFT(odd, w*w);
 
    // conquer: 재귀적으로 알아온 DFT 값들로 이번 함수의 결과를 계산
    cpx wp(1, 0);
    for(int i = 0; i < n/2; ++i){
        // f(x) = f_even(x^2) + x * f_odd(x^2)
        f[i] = even[i] + wp*odd[i];
        // f(-x) = f_even(x^2) - x * f_odd(x^2)
        f[i + n/2] = even[i] - wp*odd[i];
        wp *= w;
    }
}
// 두 다항식 a, b를 곱한 c를 계산해 돌려주는 함수. i번째 원소는 x^i의 계수
vector<cpx> multiply(vector<cpx> a, vector<cpx> b){
    // 다항식의 길이보다 큰 최소의 2의 거듭제곱수를 찾아 n으로 둔다
    int n = 1;
    while(n < a.size()+1 || n < b.size()+1) n *= 2;
    n *= 2;
    a.resize(n);
    b.resize(n);
    vector<cpx> c(n);
 
    cpx w(cos(2*PI/n), sin(2*PI/n));
 
    // FFT를 통해 두 다항식을 DFT해 둔다.
    FFT(a, w);
    FFT(b, w);
 
    // DFT한 값들끼리 곱하면 결과 다항식의 DFT값이 된다.
    for(int i = 0; i < n; ++i)
        c[i] = a[i]*b[i];
 
    // 역변환: c의 DFT 값으로부터 c의 다항식 형태를 복원한다.
    FFT(c, cpx(1, 0)/w);
    for(int i = 0; i < n; ++i){
        c[i] /= cpx(n, 0);
        c[i] = cpx(round(c[i].real()), round(c[i].imag()));
    }
    return c;
}