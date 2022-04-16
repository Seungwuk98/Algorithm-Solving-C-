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