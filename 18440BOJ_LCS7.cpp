#include <iostream>
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
        for (int i=0; i<length; ++i){
            ret += get(i);
        }
        return ret;
    }

    void print(){
        for (int i=0; i<length; ++i){
            cout.width(3);
            cout << get(i);
        } 
        cout << '\n';
    }
};

string a,b;

bset lcs_pre(int l1, int l2, int r1, int r2){
    bset s[26];
    int n = l2-l1+1, m = r2-r1+1;
    for (char i=0; i<26; ++i){
        s[i].resize(m);
        for (int j=r1; j<=r2; ++j) if (i+65 == b[j]) s[i].set(j-r1);
    }

    bset prev(m);
    for (int i=l1; i<=l2; ++i){
        bset x = s[a[i]-65] | prev;
        bset y = prev; y.shift(); y.set(0);
        prev = x & (x ^ (x - y));
    }
    return prev;
}

bset lcs_inv(int l1, int l2, int r1, int r2){
    bset s[26];
    int n = l2-l1+1, m = r2-r1+1;
    for (char i=0; i<26; ++i){
        s[i].resize(m);
        for (int j=r2; j>=r1; --j) if (i+65 == b[j]) s[i].set(r2-j);
    }

    bset prev(m);
    for (int i=l2; i>=l1; --i){
        bset x = s[a[i]-65] | prev;
        bset y = prev; y.shift(); y.set(0);
        prev = x & (x ^ (x - y));
    }
    return prev;
}

string result;

void lcs(int l1, int l2, int r1, int r2){
    if (r1>r2) return;
    if (l1 == l2){
        for (int i=r1; i<=r2; ++i){
            if (a[l1] == b[i]){
                result.push_back(b[i]); break;
            }
        }
        return;
    }
    int mid = l1 + l2 >> 1;
    int m = r2-r1+1;
    vector<int> lcs1(m+2), lcs2(m+2);
    bset prv1 = lcs_pre(l1,mid,r1,r2);
    for (int i=1; i<=m; ++i) lcs1[i] = lcs1[i-1] + prv1.get(i-1);

    bset prv2 = lcs_inv(mid+1,l2,r1,r2);
    for (int i=m; i>=1; --i) lcs2[i] = lcs2[i+1] + prv2.get(m-i);
    
    int mlcs=-1, idx = 0;
    for (int i=r1-1; i<=r2; ++i){
        int ni = i-r1+1;
        int l = lcs1[ni] + lcs2[ni+1];
        if (mlcs < l) {
            mlcs = l; idx = i;
        }
    }

    lcs(l1,mid,r1,idx);
    lcs(mid+1,l2,idx+1,r2);
}


int main(){
    cin >> a >> b;
    lcs(0,a.size()-1, 0,b.size()-1);
    cout << result.size() << '\n';
    cout << result;
}