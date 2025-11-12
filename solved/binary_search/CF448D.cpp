/**
 * @Time : 2025/1/28-10:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF448D 1800 二分查找
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 305, mod = 998244353;
ll T, n, m, k;

bool check(ll val) {
    ll cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += min(val / i, m);
        if(cnt >= k) return true;
    }
    return false;
}
// 找小于等于val的数 >= k个的最小val
void solve() {
    ll lo = 1, hi = n * m;
    while(lo < hi) {
        ll mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> m >> k;
        solve();
    }
};