/**
 * @Time : 2024/3/12-3:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * k叉树 路径和为n 且至少要有1条变长度 > d
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 1e3 + 5;
int T, n, k, d;

void solve() {
    vector<vector<ll>> cache(n + 1, vector(2, -1ll));
    function<ll(int, int)> dfs = [&](int len, int flag) -> ll {
        if(len == n) return flag;
        if(cache[len][flag] != -1) return cache[len][flag];
        ll res = 0;
        for(int w = 1; w <= min(k, n - len); w++) {
            bool nf = flag || w >= d;
            res = (res + dfs(len + w, nf)) % MOD;
        }
        return cache[len][flag] = res;
    };
    cout << dfs(0, 0) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> d;
    solve();
};