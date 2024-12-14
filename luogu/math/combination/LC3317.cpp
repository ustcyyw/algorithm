/**
 * @Time : 2024/12/13-5:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3317 数学 排列组合 第二类斯特林数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N1 = 1e3 + 5, M1 = 1e3 + 5, mod = 1e9 + 7;
ll X[N1], invF[N1], S[N1][M1];

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}
// 组合数 C(n,a) n个元素取a个
long long C(int n, int a) {
    return X[n] * invF[n - a] % mod * invF[a] % mod;
}

ll dfs(int n, int m) {
    if(S[n][m] != -1) return S[n][m];
    if((n == 0 && m == 0) || n == m) return S[n][m] = 1;
    if(m == 0 || m > n) return S[n][m] = 0;
    return S[n][m] = (dfs(n - 1, m) * m % mod + dfs(n - 1, m - 1)) % mod;
}

int init1 = []() -> int{
    memset(S, -1, sizeof(S));
    for(int i = 0; i < N1; i++) {
        for(int j = 0; j < M1; j++)
            dfs(i, j);
    }
    X[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < N1; i++) {
        X[i] = X[i - 1] * i % mod;
        invF[i] = qPow(X[i], mod - 2);
    }
    return 0;
}();

class Solution {
public:
    // n个表演者 x个节目
    int numberOfWays(int n, int x, int y) {
        ll ans = 0;
        for(int cnt = max(0, x - n); cnt < x; cnt++) {
            // 每个非空集合的得分都可能是[1,y]中的任意一个分数 因此会有qPow(y, x - cnt)因子
            ll c1 = qPow(y, x - cnt), c2 = C(x, cnt), c3 = S[n][x - cnt], c4 = X[x - cnt];
            ll temp = c1 * c2 % mod * c3 % mod * c4 % mod;
            ans = (ans + temp) % mod;
        }
        return ans;
    }
};