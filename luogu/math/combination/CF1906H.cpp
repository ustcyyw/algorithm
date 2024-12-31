/**
 * @Time : 2024/12/30-10:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1906H 2200 组合数学 动态规划
 */
/*
  * 首先s是可以任意排列的 先做一次全排列
  * 然后才关注如何从t中选字母
  *
  * 注意到z字母比较特殊 所以先考虑选了z字母 二者z字母数量得相同
  * 然后从后往前开始选
  * dp[i][j]: 截止字母i，选了t中的j个字母i与s中的字母i匹配
  * 那么t中就有c1[i] - j个字母(i+1)用于与i字母匹配
  * 要求  c1[i] - j + k <= c2[i + 1], 其中k是对于s中字母(i+1)，t中用于与它匹配的个数
  * dp[i][j] = comb(c1[i], j) * sum{dp[i + 1][k]}
  * k <= c2[i + 1] - (c1[i] - j) 且 k <= c1[i + 1]
  * 这里组合数的意义就是
  * 对于s中的字母i，共有c1[i] 其中又j个用t中的字母i匹配 另外的则用t中的字母(i+1)匹配
  * 所以是从c1[i]中选j
  *
  * 初状态 dp[25][cy1] = 1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m, c1[26], c2[26];
ll dp[26][N], sum[26][N];
string s, t;

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
ll C(int total, int a) {
    return x[total] * invF[total - a] % mod * invF[a] % mod;
}

void count(string& str, int* cnt) {
    for(char c : str)
        cnt[c - 'A']++;
}

ll solve() {
    count(s, c1), count(t, c2);
    if(c1[25] > c2[25]) return 0;
    dp[25][c1[25]] = 1, sum[25][c1[25]] = 1;
    for(int i = 24; i >= 0; i--) {
        for(int j = 0; j <= c1[i]; j++) {
            int k = min(c2[i + 1] - (c1[i] - j), c1[i + 1]);
            if(k >= 0) dp[i][j] = C(c1[i], j) * sum[i + 1][k] % mod;
            if(j > c2[i]) dp[i][j] = 0; // 从t中取的字母i比它本身的都多 不可能 因此取0
            sum[i][j] = dp[i][j];
            if(j > 0) sum[i][j] = sum[i][j] + sum[i][j - 1] % mod;
        }
    }
    ll base = x[n];
    for(int c : c1)
        base = base * invF[c] % mod;
    return base * sum[0][c1[0]] % mod;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> s >> t;
        cout << solve();
    }
};