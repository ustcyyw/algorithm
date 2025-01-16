/**
 * @Time : 2025/1/15-10:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1999F 1500 数学 排列组合
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k, zero, one;

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
ll x[N], invF[N];
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
ll C(int n, int a) {
    if(a > n) return 0;
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

void solve() {
    ll ans = 0;
    for(int i = (k + 1) / 2; i <= min(k, one); i++) {
        ans = (ans + C(zero, k - i) * C(one, i) % mod) % mod;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> k;
        one = zero = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(num == 1) one++;
            else zero++;
        }
        solve();
    }
};