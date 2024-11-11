/**
 * @Time : 2023/10/23-9:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 20;
int n, m, T, a[N];
vector<vector<long long>> cache;
vector<vector<int>> c;

long long dfs(int s, int pre) {
    if(s == 0) return 0;
    if(pre != -1 && cache[s][pre] != -1) return cache[s][pre];
    long long sat = 0;
    for(int i = 0; i < n; i++) {
        int t = 1 << i;
        if(t & s) {
            long long val = a[i] + dfs(s ^ t, i);
            if(pre != -1) val += c[pre][i];
            sat = max(sat, val);
        }
    }
    if(pre != -1) cache[s][pre] = sat;
    return sat;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> T;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int full = (1 << n) - 1;
    cache = vector(full + 1, vector(n, -1ll));
    c = vector(n, vector(n, 0));
    for(int i = 0, x, y, t; i < T; i++) {
        cin >> x >> y >> t;
        c[x - 1][y - 1] = t;
    }
    long long res = 0;
    if(m == n) res = dfs(full, -1);
    else {
        for(int u = full; u; u = (u - 1) & full) {
            if(__builtin_popcount(u) == n - m)
                res = max(res, dfs(full ^ u, -1));
        }
    }
    cout << res << endl;
}