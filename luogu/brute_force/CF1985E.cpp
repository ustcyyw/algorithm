/**
 * @Time : 2025/1/14-9:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1985E 1200 暴力枚举 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, x, y, z, k;

void solve() {
    ll ans = 0;
    for(int i = 1; i <= x; i++) {
        if(k % i != 0) continue;
        for(int j = 1, c1 = x - i + 1; j <= y; j++) {
            if(k / i % j != 0 || k / i / j > z) continue;
            ans = max(ans, (ll)c1 * (y - j + 1) * (z - k / i / j + 1));
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> x >> y >> z >> k;
        solve();
    }
};