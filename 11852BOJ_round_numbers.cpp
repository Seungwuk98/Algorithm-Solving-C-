#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct bset
{
    using word =uint64_t;
    vector<word> bit;
    int size;
    int length;
    bset(){}
    bset(int n){
        length = n;
        bit.resize(n/64 + 2);
        size = (int)bit.size();
    }

    void set(int x){
        bit[x >> 6] |= word(1) << (x & 63);
    }

    bool get(int x){
        return (bit[x >> 6] >> (x & 63)) & 1;
    }

    void resize(int n){
        length = n;
        bit.resize(n/64 + 2);
        size = (int)bit.size();
    }

    bset operator- (const bset &t){
        bset ret(length);
        bool carry = 0;
        for (int i=0; i<size; ++i){
            ret.bit[i] = bit[i] - (t.bit[i] + carry);
            carry = (ret.bit[i] > bit[i]) || (ret.bit[i] == bit[i] && carry);
        }
        return ret;
    }
    bset operator& (const bset &t){
        bset ret(length);
        for (int i=0; i<size; ++i){
            ret.bit[i] = bit[i] & t.bit[i];
        }
        return ret;
    }

    bset operator| (const bset &t){
        bset ret(length);
        for (int i=0; i<size; ++i){
            ret.bit[i] = bit[i] | t.bit[i];
        }
        return ret;
    }

    bset operator^ (const bset &t){
        bset ret(length);
        for (int i=0; i<size; ++i){
            ret.bit[i] = bit[i] ^ t.bit[i];
        }
        return ret;
    }

    void shift(){
        for (int i=size-1; i>=0; --i){
            bit[i] <<= 1;
            if (i && (bit[i-1] >> 63)) bit[i]|=1;
        }
    }

    int len(){
        int ret=0;
        for (int i=0; i<=length; ++i){
            ret += get(i);
        }
        return ret;
    }
};


string a,b,c;
int n,m;


int lcs(string &a, string &b){
    bset s[26];
    for (char i=0; i<26; ++i){
        s[i].resize(m);
        for (int j=0; j<m; ++j){
            if (b[j] == i+97) s[i].set(j);
        }
    }

    bset prev(m);
    for (int i=0; i<n; ++i){
        bset x = s[a[i]-97]|prev;
        bset y(m);
        y.bit = prev.bit; y.shift(); y.set(0);
        prev = x & (x ^ (x - y));
    }
    return prev.len();
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> a >> b;
    n = a.size(); m = b.size();
    c = a;
    reverse(c.begin(), c.end());
    int result = 0;
    int l = n;
    while (l--){
        a.push_back(a.front()); a.erase(a.begin());
        c.push_back(c.front()); c.erase(c.begin());
        result = max({result, lcs(a,b), lcs(c,b)});
    }
    cout << result;

}       