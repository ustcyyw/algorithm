/**
 * @Time : 2024/6/27-8:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1360F 状态压缩dp
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 52;
typedef long long ll;
int T, n, m, a, b;
string s[11];
vector<vector<char>> cache;
vector<vector<int>> info;

int check(int idx, char base, int u) {
    for(int i = 0; i < m; i++) {
        if(s[i][idx] == base) continue;
        int t = 1 << i;
        if(t & u) return -1;
        u |= t;
    }
    return u;
}

bool dfs(int idx, int u) {
    if(idx == n) return true;
    if(cache[idx][u] != '.') return cache[idx][u] != '*';
    for(int i = 0; i < m; i++) {
        int ns = check(idx, s[i][idx], u);
        if(ns == -1) continue;
        if(dfs(idx + 1, ns)) {
            cache[idx][u] = s[i][idx];
            info[idx][u] = ns;
            return true;
        }
    }
    cache[idx][u] = '*';
    return false;
}

void solve() {
    if(!dfs(0, 0)) {
        cout << "-1\n";
        return;
    }
    string res;
    for(int i = 0, u = 0; i < n; i++) {
        res.push_back(cache[i][u]);
        u = info[i][u];
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> m >> n;
        for(int i = 0; i < m; i++)
            cin >> s[i];
        cache = vector(n, vector(1 << m, '.'));
        info = vector(n, vector(1 << m, -1));
        solve();
    }
};