/**
 * @Time : 2024/5/15-11:23 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1183C 二分
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, k, n, a, b, m;

ll solve() {
    if(b * n >= k) return -1;
    ll lo = 0, hi = n;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(mid * a + (n - mid) * b < k) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> k >> n >> a >> b;
        cout << solve() << "\n";
    }
};