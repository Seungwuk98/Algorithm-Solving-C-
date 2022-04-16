#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

struct DynamicArray
{
    int *arr;
    int length;
    int count;
    DynamicArray() {
        length = 300;
        arr = new int[length];
        count = 0;
    }
    DynamicArray(int length) : length(length) {
        arr = new int[length];
        count = 0;
    }
    ~DynamicArray(){
        delete[] arr;
    }
    void append(int x){
        if (length == count) reassign();
        arr[count++] = x;
    }
    void reassign(){
        int *tmp = new int[length<<1];
        for (int i=0; i<length; ++i) tmp[i] = arr[i];
        delete[] arr;
        length <<= 1;
        arr = tmp;
    }

    int& operator[](int i){
        return arr[i];
    }
};

void radix_sort(int *arr, int n, int base = 32){
    int mx = arr[0];
    for (int i=1; i<n; ++i) mx = max(mx, arr[i]);
    int limit = 1;
    for (;limit<=mx; limit*=base);
    for (int exp=1; exp<limit; exp*=base){
        DynamicArray bucket[base];
        int count[base] = {0, };

        for (int i=0; i<n; ++i){
            int y = arr[i]/exp%base;
            bucket[y].append(arr[i]);
            count[y]++;
        }
        int k = 0;
        for (int i=0; i<base; ++i){
            for (int j=0; j<count[i]; ++j){
                arr[k++] = bucket[i][j];
            }
        }
    }
}


int main()
{
    fastio   
    int n; cin >> n;
    int *arr = new int[n];
    for (int i=0; i<n; ++i) cin >> arr[i];
    vector<int> left, right;
    for (int i=0; i<n; ++i) {
        if (arr[i] < 0) left.push_back(-arr[i]);
        else right.push_back(arr[i]);
    }
    radix_sort(left, left.size(), 64);
    radix_sort(right, right.size(), 64);
    int k = 0;
    for (int i=left.count-1; i>=0; --i) arr[k++] = -left[i];
    for (int i=0; i<right.count; ++i) arr[k++] = right[i];

    for (int i=0; i<n; ++i) cout << arr[i] << ' ';


    delete[] arr;
    
} // namespace std;
