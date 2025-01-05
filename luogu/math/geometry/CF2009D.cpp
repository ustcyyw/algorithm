/**
 * @Time : 2025/1/4-4:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2009D 1400 数学 几何 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, cntUp, cntDown, up[N], down[N];

void solve() {
    ll ans = 0;
    for(int i = 0; i <= n; i++) {
        ll base = up[i] * down[i];
        ans += base * (cntUp - up[i]) + base * (cntDown - down[i]);
        if(i >= 1) {
            ans += down[i] * up[i - 1] * up[i + 1];
            ans += up[i] * down[i - 1] * down[i + 1];
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        cntDown = cntUp = 0;
        fill(up, up + n + 1, 0), fill(down, down + n + 1, 0);
        for(int i = 1, x, y; i <= n; i++) {
            cin >> x >> y;
            if(y == 0) cntDown++, down[x]++;
            else cntUp++, up[x]++;
        }
        solve();
    }
};