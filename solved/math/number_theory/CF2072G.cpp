/**
 * @Time : 2025/2/26-9:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2072G 数学 数论 找规律
 */
 /*
  * 首先快速计算一些特别的base 当 n < base 时，翻转后答案还是n
  * 那么就只用关注 base <= n的情况 就将求和的范围限制在[2,min(n, k)]了
  *
  * 暴力打表几个例子之后发现
  * 会有连续的一些 base 使得翻转后的数字 之间的差值构成等差数列
  * 这是方便找规律求和的
  * 并且这些连续的部分 都是比较大的base
  * 不同部分之间的边界 就是看n / base的值来划分
  * 于是想到枚举[2, sqrt(n) + 1]，直接计算这部分的和
  * 而对应着的 n / base = i - 1的连续部分 找规律求和
  *
  * base
base + a
base + 2 * a - d
base + 3 * a - 3d
base + 4 * a - 6d
base + 5 * a - 10d
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, mod = 1e9 + 7;
ll T, n, k, ssum[N];

int init = []() -> int {
    for(ll i = 3, d = 1, sum = 0; i < N; i++, d++) {
        sum = (sum + d) % mod;
        ssum[i] = (ssum[i - 1] + sum) % mod;
    }
    return 0;
}();

ll cal(int num, int base) {
    vector<int> arr;
    while(num > 0) {
        arr.push_back(num % base);
        num /= base;
    }
    ll ans = 0, t = 1;
    for(int i = arr.size() - 1; i >= 0; i--) {
        ans = (ans + arr[i] * t) % mod;
        t *= base;
    }
    return ans;
}

void solve() {
    ll ans = 0;
    if(k >= n) {
        ans = (k - n) % mod * n % mod;
        k = n;
    }
    // i <= hi 避免了重复计算
    for(int i = 2, lo, hi = k; i <= min(k, (ll)sqrt(n) + 1) && i <= hi; i++) {
        ans = (ans + cal(n, i)) % mod;
        lo = max(n / i + 1, i + 1ll);
        if(lo <= hi) {
            ll m = hi - lo + 1;
            ll base = cal(n, hi), d = (i - 1) * 2;
            ll pre = cal(n, hi - 1), a = pre - base;
            ans = (ans + base * m % mod + m * (m - 1) / 2 % mod * a % mod) % mod;
            ans = (ans - ssum[m] * d % mod + mod) % mod;
            hi = lo - 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        solve();
    }
}