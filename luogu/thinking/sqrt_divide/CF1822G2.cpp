/**
 * @Time : 2024/5/28-11:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1822G2 根号分治 数论
 */
/* 等比数列 枚举中间项 aj
 * 前项ai是aj的一个因子 倍数为b 那么后项ak = b * aj
 * 如果 aj < 1e6. 那么aj的因子只有2e3个
 * 如果 aj >= 1e6. aj * 1000就超过最大数 那么b就从1枚举到 maxV / aj
 * 根号分治
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int T, n;
map<ll, ll> mp;

void solve() {
    ll ans = 0, maxV = mp.rbegin()->first;
    for(auto& [v, c] : mp) { // 枚举中间项
        if(c >= 3) ans += c * (c - 1) * (c - 2);
        ll b = v >= (ll)1e6 ? maxV / v : sqrt(v);
        for(ll j = 1; j <= b; j++) {
            // 前项和后项都能找到的情况
            if(v % j != 0) continue;
            if(j != 1 && mp.count(v / j) && mp.count(v * j))
                ans += c * mp[v / j] * mp[v * j];
            ll a = v / j;
            if(a != 1 && a != j && mp.count(v / a) && mp.count(v * a))
                ans += c * mp[v / a] * mp[v * a];
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        mp.clear();
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            mp[num]++;
        }
        solve();
    }
};