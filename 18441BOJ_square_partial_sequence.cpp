#define private public
#include <bitset>
#include <iostream>
#undef private

#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

template<size_t _Nw> void _M_do_sub(_Base_bitset<_Nw> &A, const _Base_bitset<_Nw> &B) {
	for(int i=0, c=0; i<_Nw; i++)
		c=_subborrow_u64(c, A._M_w[i], B._M_w[i], (unsigned long long*)&A._M_w[i]);
}
template<> void _M_do_sub(_Base_bitset<1> &A, const _Base_bitset<1> &B) {
	A._M_w-=B._M_w;
}
template<size_t _Nb> bitset<_Nb>& operator-=(bitset<_Nb> &A, const bitset<_Nb> &B) {
	_M_do_sub(A, B);
	return A;
}
template<size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb> &A, const bitset<_Nb> &B) {
	bitset<_Nb> C(A);
	return C-=B;
}


template<size_t _Nw> void _M_do_add(_Base_bitset<_Nw> &A, const _Base_bitset<_Nw> &B) {
	for(int i=0, c=0; i<_Nw; i++)
		c=_addcarry_u64(c, A._M_w[i], B._M_w[i], (unsigned long long*)&A._M_w[i]);
}
template<> void _M_do_add(_Base_bitset<1> &A, const _Base_bitset<1> &B) {
	A._M_w+=B._M_w;
}
template<size_t _Nb> bitset<_Nb>& operator+=(bitset<_Nb> &A, const bitset<_Nb> &B) {
	_M_do_add(A, B);
	return A;
}
template<size_t _Nb> inline bitset<_Nb> operator+(const bitset<_Nb> &A, const bitset<_Nb> &B) {
	bitset<_Nb> C(A);
	return C+=B;
}

template<size_t sz>
string do_lcs(const string &a, const string &b){
    int n = a.size(), m = b.size();
    bitset<sz> S[26];
    for (int j=0; j<m; ++j) S[b[j]-'a'][j] = 1;
    

    bitset<sz> P[n+1], x; 
    for (int i=1; i<=n; ++i){
        x = S[a[i-1]-'a'] | P[i-1];
        P[i] = P[i-1] << 1; P[i][0] = 1;
        P[i] = x & (x ^ (x - P[i]));
    }

    string ret;
    for (int x=n, y=m-1;x>0;x--){
        while (y>=0 && !P[x][y]) y--;
        if (y<0) break;
        while (x>0 && P[x-1][y]) x--;
        ret.push_back(b[y--]);
    }
    reverse(ret.begin(), ret.end());
    return ret;

}

string lcs(const string &a, const string &b){
    int m = b.size();
    if (m<=64) return do_lcs<64>(a,b);
    if (m<=128) return do_lcs<128>(a,b);
    if (m<=192) return do_lcs<192>(a,b);
    if (m<=256) return do_lcs<256>(a,b);
    if (m<=320) return do_lcs<320>(a,b);
    if (m<=384) return do_lcs<384>(a,b);
    if (m<=448) return do_lcs<448>(a,b);
    if (m<=512) return do_lcs<512>(a,b);
    if (m<=576) return do_lcs<576>(a,b);
    if (m<=640) return do_lcs<640>(a,b);
    if (m<=704) return do_lcs<704>(a,b);
    if (m<=768) return do_lcs<768>(a,b);
    if (m<=832) return do_lcs<832>(a,b);
    if (m<=896) return do_lcs<896>(a,b);
    if (m<=960) return do_lcs<960>(a,b);
    if (m<=1024) return do_lcs<1024>(a,b);
    if (m<=1088) return do_lcs<1088>(a,b);
    if (m<=1152) return do_lcs<1152>(a,b);
    if (m<=1216) return do_lcs<1216>(a,b);
    if (m<=1280) return do_lcs<1280>(a,b);
    if (m<=1344) return do_lcs<1344>(a,b);
    if (m<=1408) return do_lcs<1408>(a,b);
    if (m<=1472) return do_lcs<1472>(a,b);
    return do_lcs<1536>(a,b);
    
}

int T;
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> T;
    for (int i=1; i<=T; ++i){
        string a; cin >> a;
        int n = a.size();
        string x, y = a,ans;
        for (int i=0; i<n; ++i){
            x.push_back(y.front()); y.erase(y.begin());
            string ret = x.size() < y.size()? lcs(y,x) : lcs(x,y);
            if (ans.size() < ret.size()) ans = ret;
        }
        cout << "Case #" << i << ": " << ans.size()*2 <<'\n';
        if (ans.size()) cout << ans << ans << '\n';
    }
}