/**
 * @Time : 2025/1/26-1:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF18B 1700 数学 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 205, mod = 998244353;
ll T, n, d, m, l;

void solve() {
    for(int k = 0; k < n; ) {
        ll r = m * k + l, c = r / d + 1;
        ll x = c * d;
        while(k < n && k * m + l <= x) k++;
        ll lo = k == n ? LONG_LONG_MAX : k * m;
        if(lo > x) {
            cout << x;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> d >> m >> l;
        solve();
    }
};