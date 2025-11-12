/**
 * @Time : 2025/1/4-4:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2009E 1400 二分答案 数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, k;

ll cal(int m) {
    return (k + k + m - 1) * m / 2;
}

void solve() {
    ll total = cal(n);
    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        ll s1 = cal(mid), s2 = total - s1;
        if(s1 < s2) lo = mid + 1;
        else hi = mid;
    }
    cout << min(abs(total - cal(lo) - cal(lo)), abs(total - cal(lo - 1) - cal(lo - 1))) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        solve();
    }
};