/**
 * @Time : 2025/4/5-11:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF817C 1600 思维题 暴力枚举
 */
 /*
  * 如果n <= s， 那么任何一个小于等于n的数 再减去数位上的各个数字 一定小于s
  * 所以只需要考虑 [s + 1, n] 上的数字
  * 如果s一共有m位，所有大于 t = s + 9 * m 的数，其每一位数位即便是最大的9 减去之后也依旧大于s
  * 因此所有 [t + 1, n] 上的数 一定是满足条件的数
  * 正真需要check的数 只有 [s + 1, t]上的数 总共就9 * m个 暴力枚举即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 15, M = 30;
ll n, s;

bool check(ll num) {
    ll cnt = 0, temp = num;
    while(temp) {
        cnt += temp % 10;
        temp /= 10;
    }
    return num - cnt >= s;
}

ll solve() {
    if(s >= n) return 0;
    int m = to_string(s).size();
    ll t = min(n, s + m * 9);
    ll ans = 0;
    for(ll num = s + 1; num <= t; num++)
        ans += check(num);
    return ans + n - t;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s;
    cout << solve();
}