#define _USE_MATH_DEFINES
#include <iostream>
#include <complex>
#include <algorithm>
#include <vector>
using namespace std;

typedef complex<double> cpx;
typedef vector<cpx> vec;
typedef long long lint;
const double pi = acos(-1);

void fft(vec &a, bool inv){
    int n = a.size();
    for(int i=1, j=0; i<n; i++){
        int bit = n >> 1;
        for(; bit<=j; bit>>=1) j -= bit;
        j += bit;
        if(i < j) swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len<<=1){
        double ang = 2 * M_PI / len;
        if(inv) ang = -ang;
        cpx w(cos(ang), sin(ang));
        for(int i=0; i<n; i+=len){
            cpx wp(1, 0);
            for(int j=0; j<len/2; j++){
                cpx u = a[i + j], v = a[i + j + len/2] * wp;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                wp *= w;
            }
        }
    }
    if(inv){
        for(int i=0;i<n;i++){
			a[i] /= n;
			a[i] = cpx(round(a[i].real()), round(a[i].imag())); //result is integer
		}
    }
}

vector<lint> mul(const vector<lint> &a, const vector<lint> &b){
	vec aa(a.begin(), a.end()), bb(b.begin(), b.end());
	int n = 1; while(n <= max(a.size(), b.size())) n <<= 1;
	aa.resize(n), bb.resize(n);
	fft(aa, 0), fft(bb, 0);
	for(int i=0; i<n; i++) aa[i] *= bb[i];
	fft(aa, 1);
	vector<lint> ret(n);
	for (int i = 0; i < n; i++){
		ret[i] = round(aa[i].real());
		if(ret[i]) ret[i] = 1;
	}
	//while(ret.size() > 10 && ret.back() == 0) ret.pop_back();
	return ret;
}

vector<lint> pw(vector<lint> &a, int k){
    vector<lint> r=a; k--;
    while (k){
        if (k&1) r = mul(r, a);
        a = mul(a,a);
        k>>=1;
    } return r;
}


vector<lint> a(1024);
int n,k;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> k;
    while (n--){
        int x; cin >> x;
        a[x]=1;
    }
    vector<lint> result = pw(a, k);
    for (int i=0; i<result.size(); ++i){
        if (result[i]) cout << i << " ";
    }
}