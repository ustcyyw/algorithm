/**
 * @Time : 2025/2/14-10:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF616E 2200 数学 数论
 */
 /*
  * 求余数 做带余数的除法操作
  * 会发现除数为一个连续区间[i,j]上的数时，除法的结果相同 余数构成等差数列
  * 并且除法的结果的量级在1e7以下 那么只要不断找到区间边界就能快速计算结果
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5, mod = 1e9 + 7, INF2 = 500000004;
ll T, n, m, ans = 0;

// 找到最大的j使得 n / i == n / j
ll find(ll i) {
    if(n / i != n / (i + 1)) return min(i, m);
    ll lo = i, hi = m;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(n / mid != n / i) hi = mid - 1;
        else lo = mid;
    }
    return lo;
}

void solve() {
    for(ll i = 1; i <= m; ) {
        ll j = find(i), cnt = j - i + 1;
        ll a1 = n % i, an = n % j;
        ans = (ans + (a1 + an) % mod * (cnt % mod) % mod * INF2 % mod) % mod;
        i = j + 1;
    }
    cout << (long long)ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> m;
        solve();
    }
};