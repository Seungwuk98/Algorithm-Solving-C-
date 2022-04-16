#include <iostream>

using namespace std;


int main()
{
    string a;
    cin >> a;
    int n = a.size();
    int ret[26] = {0,};
    for (auto x : a) ret[x-'A']++;
    if (~n&1){
        for (auto x : ret) if (x&1) {
            cout << "I'm Sorry Hansoo"; return 0;
        }
    } else {
        int cnt = 0;
        for (auto x : ret) if (x&1) {
            cnt ++; if (cnt > 1) {
                cout << "I'm Sorry Hansoo"; return 0;
            }
        }
    }
    string result = string(n,'A');
    int j = 0, k = n-1;
    for (int i=0; i<26; ++i){
        while (ret[i] > 1){
            result[j] = result[k] = i+'A';
            j++; k--;
            ret[i] -= 2;
        }
        if (ret[i]&1) result[n>>1] = i+'A';
    }
    cout << result;


} // namespace std;
