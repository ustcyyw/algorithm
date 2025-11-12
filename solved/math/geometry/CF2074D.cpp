/**
 * @Time : 2025/3/12-10:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2074D 1461 暴力枚举 数学 几何
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, P = 13331;
int T, n, m, x[N], r[N];
map<int, int> mp;

void cal(ll x, ll r) {
    for(int i = x - r; i <= x + r; i++) {
        ll lo = 0, hi = r, d = (ll)(i - x) * (i - x);
        while(lo < hi) {
            ll mid = (lo + hi + 1) >> 1;
            if(mid * mid + d > r * r) hi = mid - 1;
            else lo = mid;
        }
        mp[i] = max(mp[i], (int)lo);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        mp = {};
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> x[i];
        for(int i = 1; i <= n; i++) {
            cin >> r[i];
            cal(x[i], r[i]);
        }
        ll ans = 0;
        for(auto& p : mp)
            ans += 2 * p.second + 1;
        cout << ans << "\n";
    }
}