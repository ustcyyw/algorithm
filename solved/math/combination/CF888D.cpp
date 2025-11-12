/**
 * @Time : 2025/3/26-9:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF888D 1600 数学 组合数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, mod = 1e9 + 7;
ll T = 1e9 + 10, n, k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    ll ans = 1;
    if(k >= 2) ans += n * (n - 1) / 2;
    if(k >= 3) ans += n * (n - 1) * (n - 2) / 6 * 2;
    if(k >= 4) ans += n * (n - 1) * (n - 2) * (n - 3) / 24 * 9;
    cout << ans;
}