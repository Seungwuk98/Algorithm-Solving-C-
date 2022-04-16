#include <bits/stdc++.h>

using namespace std;
using ll = long long;
/*********Pseudo Random Number*******
  적당한 의사 난수를 생성
*************************************/
ll R = 2342305;
ll A = 2305953;
ll B = 59843860;
ll M = 1000000007;
ll rnd() { return R = (A*R%M + B)%M; }
/*********Pseudo Random Number********/

int partition(int *a, int s, int e){
    /*************************************
    배열 a의 [s, e] 범위를 a[e]를 피벗으로 partition한다.
    **************************************/
    int i = s;
    for (int j=s; j<e; ++j) if (a[j] <= a[e]) swap(a[i++], a[j]);
    swap(a[e], a[i]);
    return i;
}

bool isone(int *a, int s, int e){
    /************************************
    배열 a의 [s, e] 범위의 모든 원소가 1개로 이루어져있는지 판단.
    *************************************/
    for (int i=s; i<e; ++i) if (a[i] != a[e]) return false;
    return true;
}

int random_selection(int *a, int s, int e, int i){
    /************************************
    의사 난수로 피벗을 정한 뒤, 그를 이용해 partition하는 방법
    배열 a의 [s, e] 범위에서 i번째 원소를 select 한다.
    *************************************/
    if (s==e || isone(a, s, e)) return a[s];
    int p = rnd()%(e-s+1)+s;
    swap(a[e], a[p]);
    int q = partition(a, s, e);
    int diff = q-s+1;
    if (i < diff) return random_selection(a, s, q-1, i);
    else if (i==diff) return a[q];
    else return random_selection(a, q+1, e, i-diff);
}

int insertion_sort(int *a, int s, int e){
    /*************************************
    배열 a의 [s, e] 범위를 insertion sort한다.
    *************************************/
    for (int i=s+1; i<=e; ++i) 
        for (int j=i; j>s && a[j] < a[j-1]; --j)
            swap(a[j], a[j-1]);
}

int linear_selection(int *a, int s, int e, int i){
    /**************************************
    5칸씩 나누어 대략적인 중앙값을 구하여 이를 이용해 partition하는 방법
    배열 a의 [s, e] 범위에서 i번째 원소를 select 한다.
    **************************************/
    if (isone(a, s, e)) return a[s];
    if (e-s+1 <= 5) { // 개수가 5 이하면 정렬 후 답을 리턴
        insertion_sort(a, s, e);
        return a[s+i-1];
    }
    /***************5개씩 분할***************
    각 분할의 중앙값을 [s, e] 구간의 맨 앞으로 swap
    중앙값이 모인 부분만 재귀 호출
    *****************************************/
    int z = s;
    for (int x=s; x<=e; x+=5){
        int y = min(x+5, e);
        insertion_sort(a, x, y);
        swap(a[z++], a[x+y>>1]);
    }
    int mid = linear_selection(a, s, z-1, z-s>>1);
    for (int x=s; x<=e; ++x) if (a[x] == mid) {
        mid = x; break;
    }
    /***************5개씩 분할***************/
    
    swap(a[e], a[mid]);
    int q = partition(a, s, e);
    int diff = q-s+1;
    if (i == diff) return a[q];
    if (i < diff) return linear_selection(a, s, q-1, i);
    return linear_selection(a, q+1, e, i-diff);
}

bool checker_ith_element(int *a, int ans, int n, int i) {
    /****************************************
    ans가 배열 a의 i번째 수가 되기 위한 조건
    (1) ans 미만의 수가 i개 미만
    (2) ans 이하의 수가 i개 이상
    *****************************************/
    int below = 0, under = 0;
    for (int i = 0; i < n; ++i){
        if (a[i] <= ans){
            below++;
            if (a[i] ^ ans) under++;
        }
    }
    return under < i && below >= i;
}

using namespace chrono;
int a[100000000], b[100000000];
int main()
{
    /*************file stream*************/
    ifstream cin_input;
    cin_input.open("input.txt");
    ofstream cout_random, cout_deter, cout_result;
    cout_random.open("random.txt");
    cout_deter.open("deter.txt");
    cout_result.open("result.txt");
    cin_input.tie(0); ios_base::sync_with_stdio(0);
    /*************file stream*************/
    
    /*************define & input**************/
    int n,k;
    cin_input >> n;
    for (int i=0; i<n; ++i) cin_input >> a[i];
    copy(a, a+n, b);
    cin_input >> k;
    system_clock::time_point start, end;
    milliseconds micro;
    /*************define & input**************/


    /*************random select***************/
    start = system_clock::now();
    int ans_random;
    cout_random << (ans_random = random_selection(a, 0, n-1, k)) << '\n';
    end = system_clock::now();
    micro = duration_cast<milliseconds> (end - start);
    cout_random << micro.count() << "ms" << '\n';
    /*************random select***************/

    /*************linear select***************/
    start = system_clock::now();
    int ans_linear;
    cout_deter << (ans_linear = linear_selection(b, 0, n-1, k)) << '\n';
    end = system_clock::now();
    micro = duration_cast<milliseconds> (end - start);
    cout_deter << micro.count() << "ms" << '\n';
    /*************linear select***************/

    /*************checker program*************/
    cout_result << checker_ith_element(a, ans_random, n, k) << '\n';
    cout_result << checker_ith_element(a, ans_linear, n, k) << '\n';
    /*************checker program*************/

    /*************file close*************/
    cin_input.close();
    cout_random.close();
    cout_deter.close();
    cout_result.close();
    /*************file close*************/
} // namespace std;
