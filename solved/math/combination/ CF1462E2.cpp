/**
 * @Time : 2024/7/7-4:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1462E2 暴力枚举 组合数学 双指针
 */
 /*
  * 暴力枚举最小值 以及最小值的个数
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k, cnt[N];

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
    ll ans = 0;
    for(int i = 1, j = 1, sum = 0; i <= n; i++) {
        while(j <= n && j - i <= k) sum += cnt[j++];
        for(int c1 = max(1, m - sum + cnt[i]); c1 <= min(m, cnt[i]); c1++) {
            ll t1 = C(cnt[i], c1), t2 = C(sum - cnt[i], m - c1);
            ans = (ans + t1 * t2 % mod) % mod;
        }
        sum -= cnt[i];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        fill(cnt, cnt + n + 1, 0);
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            cnt[num]++;
        }
        solve();
    }
};