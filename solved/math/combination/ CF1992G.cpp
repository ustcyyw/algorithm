/**
 * @Time : 2024/7/16-3:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1992G 数学 排列组合
 */
/*
 * 假设n个排列 最大的值 就是全集的时候
 * 2 * n + 1 这是最大值
 * 可能的取值范围 1 ～ 2n + 1
 *
 * 但凡sublen + sublen + 1 > n 那么加和的最大元素 一定超过n 就是 2 * sublen + 1为贡献的值
 * 而且 组别数为 C(n, sublen)
 * 如果 2 * len + 1 < n 那么最大的元素 有可能会变化
 * 元素值最小为 len + 1 最大也就是2 * len + 1 因为总共就2 * len + 1个数
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 5e4 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n;

/*
 * 求mod意义下的逆元
 */
// qPow(total, mod - 2, mod);
long long qPow(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
long long x[N], invF[N];
int init = []() -> int {
    x[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] * i % mod;
        invF[i] = qPow(x[i], mod - 2);
    }
    return 0;
}();

// 组合数 C(n,a) n个元素取a个
long long C(int n, int a) {
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

void solve() {
    ll ans = 1 + 2 * n + 1;
    for(int len = 1; len <= n - 1; len++) { // 枚举子数组长度
        if(2 * len + 1 > n) ans = (ans + (2 * len + 1) * C(n, len) % mod) % mod;
        else {
            // 枚举可能出现的值 i不能出现在子数组中 补充的数最大值刚好是i
            // 就意味着 如果比i小的数less个 less + len + 1 = i
            for(int i = len + 1; i <= 2 * len + 1; i++) {
                int less = i - 1 - len, more = len - less;
                ans = (ans + i * C(i - 1, less) % mod * C(n - i, more) % mod) % mod;
            }
        }
    }
    cout << ans << "\n";
}
// 暴力对拍
//void solve2() {
//    ll full = 1 << n;
//    ll ans = 1;
//    map<int, ll> mp;
//    for(ll u = 1; u < full; u++) {
//        int len = __builtin_popcount(u), need = len + 1;
//        for(int i = 0; ; i++) {
//            if(((1ll << i) & u) == 0) {
//                need--;
//                if(need == 0) {
//                    mp[i + 1]++;
//                    break;
//                }
//            }
//        }
//    }
//    for(auto& p : mp) {
////        cout << p.first << " " << p.second << "\n";
//        ans = (ans + p.first * p.second % mod) % mod;
//    }
//    cout << ans << "\n";
//}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        solve();
    }
};