#include <iostream>
#include <unordered_map>
using namespace std;
#define MAX_N 1000
// 변수 선언
int n, k;
int arr[MAX_N];
unordered_map<int, int> freq;
int main() {
    // 입력:
    cin >> n >> k;
    int ans = 0;
    // 각 숫자가 몇 번씩 나왔는지를
    // hashmap에 기록해줍니다.
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    // 배열을 앞에서부터 순회하며 쌍을 만들어줍니다.
    for(int i = 0; i < n; i++) {
        // 이미 순회한 적이 있는 숫자는 빼 버림으로서
        // 같은 조합이 여러번 세어지는 걸 방지합니다.
        for(int j = 0; j < i; j++) {
            // 전처리를 해주었기 때문에 이미 순회한 적 있는 값은 hashmap에 없습니다.
            // 이와 같은 방식으로 같은 조합이 중복되어 세어지는 걸 방지할 수 있습니다.
            if(freq.count(k - arr[i] - arr[j]) > 0)
                ans += freq[k - arr[i] - arr[j]];
        }
        freq[arr[i]]++;
    }
    cout << ans;
}