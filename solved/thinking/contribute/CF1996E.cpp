/**
 * @Time : 2024/12/2-11:35 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1996E 1600 前缀和 贡献值 hash表
 */
 /*
  * 0设置为-1 区间和为0就是是一个符合条件的组
sum[1] = 1, sum[5] = 1, sum[7] = 1, sum[11]
(2,5)    2 * (n - 5 + 1)
(2,7), (6,7)  2 * (n - 7 + 1) + 6 * (n - 7 + 1)
(2,11), (6,11), (8,11)  (2 + 6 + 8) * (n - 11 + 1)
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n;
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> s;
        n = s.size(), s = '.' + s;
        map<ll, ll> psm;
        psm[0] = 1;
        ll ans = 0;
        for(int i = 1, sum = 0; i <= n; i++) {
            sum += s[i] == '1' ? 1 : -1;
            ans = (ans + psm[sum] * (n - i + 1) % mod) % mod;
            psm[sum] = (psm[sum] + i + 1) % mod;
        }
        cout << ans << "\n";
    };
};