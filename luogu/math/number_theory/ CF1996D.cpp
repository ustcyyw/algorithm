/**
 * @Time : 2024/12/2-3:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1996D 1500 暴力枚举 数学  参考了答案
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, x;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> x;
        ll ans = 0;
        for(ll a = 1; a < x; a++) {
            for(ll b = 1; a * b < n && a + b < x; b++) {
                ll  t = min(x - a - b, (n - a * b) / (a + b));
                ans += t;
            }
        }
        cout << ans << "\n";
    };
};