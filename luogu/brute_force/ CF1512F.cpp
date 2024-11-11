/**
 * @Time : 2024/7/9-8:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1512F 贪心 + 暴力枚举
 */
 /*
  * 暴力枚举最后是在哪个公司待到钱足够
  * 因为a是单调增的 对于特定的最后一家公司 肯定是要尽快到达最好
  */

#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, a[N], b[N], c;

void solve() {
    ll ans = 1e9;
    for(ll i = 1, day = 0, money = 0; i <= n; i++) {
        ll need = c - money, t = need % a[i] == 0 ? need / a[i] : need / a[i] + 1;
        ans = min(ans, t + day);
        need = b[i] - money;
        if(need <= 0) need = 0;
        t = need % a[i] == 0 ? need / a[i] : need / a[i] + 1;
        day += 1 + t, money = money + t * a[i] - b[i];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> c;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i < n; i++)
            cin >> b[i];
        solve();
    }
};