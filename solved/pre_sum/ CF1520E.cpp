/**
 * @Time : 2024/7/10-10:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1520E 前缀和
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, suf[N];
string s;

void solve() {
    ll sum = 0, cnt = 0, ans = LONG_LONG_MAX;
    suf[n + 1] = 0;
    for(int i = n; i >= 1; i--) {
        if(s[i] == '*') cnt++, sum += i;
        suf[i] = sum - cnt * i - (cnt - 1) * cnt / 2;
    }
    sum = 0, cnt = 0;
    for(int i = 0; i <= n; i++) {
        if(s[i] == '*') cnt++, sum += i;
        ll temp = cnt * i - sum - (cnt - 1) * cnt / 2 + suf[i + 1];
        ans = min(temp, ans);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> s;
        s = '.' + s;
        solve();
    }
};