/**
 * @Time : 2025/4/23-11:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2091D 1200 二分答案
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e3 + 15, mod = 998244353;
int T, n, m, k;

void solve() {
    int lo = 1, hi = m;
    while(lo < hi) {
        int mid = (lo + hi) >> 1, cnt = m / (mid + 1);
        ll ans = cnt * mid + m - cnt * (mid + 1);
        if(ans * n >= k) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        solve();
    }
}