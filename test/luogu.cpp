/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, k, a[N], b[N];

ll count(ll num1, ll num2, int val) {
    if(num1 < val) return 0;
    return (num1 - val) / num2 + 1;
}

bool check(int val) {
    ll cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += count(a[i], b[i], val);
        if(cnt >= k) return true;
    }
    return false;
}

void solve() {
    int lo = 0, hi = 1e9;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll cnt = count(a[i], b[i], lo + 1);
        ans += (a[i] - (cnt - 1) * b[i] + a[i]) * cnt / 2;
        k -= cnt;
    }
    ans += (ll)lo * k;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        solve();
    };
};