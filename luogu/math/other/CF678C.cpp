/**
 * @Time : 2025/2/16-10:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF678C 1600 贪心 数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 1e9 + 7;
ll T, n, a, b, p, q;

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> a >> b >> p >> q;
        ll ans = n / a * p + n / b * q;
        ll num = lcm(a, b), cnt = n / num;
        ans -= cnt * min(p, q);
        cout << ans << "\n";
    }
};