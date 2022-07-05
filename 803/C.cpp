#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> arr;
        int x, zero = 0, minus = 0, plus = 0;
        for (int i=0; i<n; ++i) {
            cin >> x;
            if (x < 0) minus++;
            else if (x > 0) plus++;
            else zero ++;

            if (x == 0) {
                if (zero < 2) arr.push_back(x); 
            } else {
                arr.push_back(x);
            }
        }

        if (minus > 2 || plus > 2) {
            cout << "NO\n";
            continue;
        }

        bool cc = 0;
        auto find = [&](int x) {
            bool c = 0;
            for (int i=0; i<arr.size(); ++i) if (arr[i] == x) {
                c = 1;
                break;
            }
            return c;
        };
        for (int i=0; i<arr.size(); ++i) for (int j=i+1; j<arr.size(); ++j) for (int k=j+1; k<arr.size(); ++k) {
            if (!find(arr[i] + arr[j] + arr[k])) {
                cc = 1;
                break;
            }
        }
        if (cc) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";


    }
} // namespace std;
