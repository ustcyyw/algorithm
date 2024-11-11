/**
 * @Time : 2024/5/28-9:40 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1822G1 数论
 */
 /*
  * sum(1/sqrt(n)) = 2 * sqrt(n)
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int T, n;
map<ll, ll> mp;

void solve() {
    ll ans = 0, maxV = mp.rbegin()->first;
    for(auto& [v, c] : mp) {
        if(c >= 3) ans += c * (c - 1) * (c - 2);
        ll b = sqrt(maxV / v);
        for(ll j = 2; j <= b; j++) {
            if(mp.count(v * j) && mp.count(v * j * j)) {
                ans += c * mp[v * j] * mp[v * j * j];
            }
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