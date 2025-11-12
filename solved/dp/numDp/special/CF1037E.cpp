/**
 * @Time : 2025/5/16-4:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1037E 2300 数位dp 特殊问题 求数字之和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, mod = 998244353;
ll T, l, r, k;

/*
 * f[i][s]: 到第i位 已使用的数字状态为s的方案数量
 * g[i][s]: 到第i位 已使用的数字状态为s的数字总和
 * 枚举当前位的数字
 * g[i][s] += g[i+1][s1] + base * f[i+1][s1]
 * f[i][s] += f[i+1][s1]
 * s1 = s | (1 << num)
 */
ll solve(ll n) {
    string s = to_string(n);
    int m = s.size(), full = 1 << 10;
    vector<vector<vector<ll>>> f(m + 1, vector(full, vector(2, -1ll)));
    function<vector<ll>(int, int, bool, bool)> dfs =
            [&](int i, int status, bool limit, bool is_num) -> vector<ll> {
                if(i == m) return {is_num && __builtin_popcount(status) <= k, 0};
                if(!limit && is_num && f[i][status][0] != -1) return f[i][status];
                vector<ll> ans = {0, 0};
                if(!is_num) ans = dfs(i + 1, status, false, false);
                int up = limit ? s[i] - '0' : 9, down = is_num ? 0 : 1;
                ll base = pow(10, m - i - 1);
                for(int j = down; j <= up; j++) {
                    int ns = status | (1 << j);
                    vector<ll> temp = dfs(i + 1, ns, j == up && limit, true);
                    ans[0] = (ans[0] + temp[0]) % mod;
                    ans[1] = (ans[1] + temp[1] + j * base % mod * temp[0] % mod) % mod;
                }
                if(!limit && is_num) f[i][status] = ans;
                return ans;
            };
    return dfs(0, 0, true, false)[1];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> l >> r >> k;
        cout << (solve(r) - solve(l - 1) % mod + mod) % mod << "\n";
    }
}