/**
 * @Time : 2024/9/4-10:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1811G2 线性动态规划 数学
 */
/*
  * m是k的倍数 n, k < 5000
  * 选取的子序列被分割成颜色相等m个部分， 每个部分都有k个元素

dp[i]：以第i个元素结尾的最大部分数（因为每个部分长度都为k，最长路径对应最大部分数）
cnt[i]：以第i个元素结尾的最大部分数的方案数
dp[i] = dp[j - 1] + 1, if sum[j, i] of nums[i] >= k
cnt[i] = cnt[j - 1] * comb(total, k), if dp[j - 1] + 1 == dp[i]

dp[0] = 0, cnt[0] = 1

 简单版本只有数据范围变小 代码不用改任何
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 5e3 + 5, mod = 1e9 + 7;
int T, n, k, nums[N];

ll qPow(long long x, long long y) {
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
ll comb(int n, int a) {
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

void solve() {
    vector<ll> dp(n + 1, -1), cnt(n + 1, 0);
    dp[0] = 0, cnt[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int c = 0, j = i; j >= 1; j--) {
            if(nums[j] == nums[i]) c++;
            if(c < k || dp[j - 1] == -1) continue;
            ll temp = comb(c - 1, k - 1); // 除了nums[i]，还要拿k-1个元素
            if(dp[j - 1] + 1 > dp[i]) {
                dp[i] = dp[j - 1] + 1;
                cnt[i] = cnt[j - 1] * temp % mod;
            } else if(dp[j - 1] + 1 == dp[i])
                cnt[i] = (cnt[i] + cnt[j - 1] * temp % mod) % mod;
        }
    }
    ll ans = 1, len = 0;
    for(int i = 1; i <= n; i++) {
        if(len < dp[i]) len = dp[i], ans = cnt[i];
        else if(len == dp[i]) ans = (ans + cnt[i]) % mod;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};