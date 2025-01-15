/**
 * @Time : 2025/1/14-9:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1985F 1500 二分答案
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, h, n, a[N], c[N];

bool check(ll time) {
    time--;
    ll total = 0;
    for(int i = 1; i <= n; i++) {
        total += (ll)(time / c[i] + 1) * a[i];
        if(total >= h) return true;
    }
    return false;
}

void solve() {
    ll lo = 1, hi = 5e10;
    while(lo < hi) {
        ll mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> h >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> c[i];
        solve();
    }
};