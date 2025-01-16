/**
 * @Time : 2025/1/15-10:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1999E 1300 贪心 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, l, r, sum[N];

int cal(int num) {
    int cnt = 0;
    while(num) {
        num /= 3, cnt++;
    }
    return cnt;
}

int init = []() -> int {
    for(int i = 1; i < N; i++)
        sum[i] = sum[i - 1] + cal(i);
    return 0;
}();

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> l >> r;
        ll ans = cal(l) * 2 + sum[r] - sum[l];
        cout << ans << "\n";
    }
};