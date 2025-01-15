/**
 * @Time : 2025/1/14-9:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1985G 1600 数学 快速幂
 */
/*
  * 如果k=10  k * D(n) 是十倍
但是 k * n 每一位上的数字最多变为原来的9倍 最多是9倍D(n)
0比较特殊 在等式左右都没有任何贡献

k >= 10, 不可能 返回0
k = 1，就是求10^l到10^r次中间有多少个数 10^r - 10^l + 1
其余的k，每一位可以取的数字是 0..b, 其中b是使得 k * b <= 9 成立的最大值
l, r标识的是数位数量
第一位取1..b 其余位随便取0..b
b * (b+1) ^ (l) + b * (b+1) ^ (l+1) + ... + b * (b+1) ^ (r-1) + 1
等比数列求和(b+1) ^ r - (b+1) ^ l
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 5, mod = 1e9 + 7;
int T, n, l, r, k;

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

ll solve() {
    if(k >= 10) return 0;
    if(k == 1)
        return (qPow(10, r) - qPow(10, l) + mod) % mod;
    int base = 9 / k;
    return (qPow(base + 1, r) - qPow(base + 1, l) + mod) % mod;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> l >> r >> k;
        cout << solve() << "\n";
    }
};