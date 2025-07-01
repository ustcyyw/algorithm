/**
 * @Time : 2025/6/28-11:29
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2117F 1800 思维题
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
int T, n, cc, node, leaf1, leaf2;
vector<vector<int>> graph;

ll qPow(ll x, ll y) {
    if(y < 0) return 1;
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

void dfs(int f, int v, int d) {
    if(f != -1 && graph[v].size() == 1) {
        cc++;
        if(leaf1 == -1) leaf1 = d;
        else leaf2 = d;
        return;
    }
    if(graph[v].size() > 2 || (f == -1 && graph[v].size() == 2)) node = d;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(v, w, d + 1);
    }
}

ll solve() {
    dfs(-1, 1, 1);
    if(cc > 2) return 0;
    if(cc == 1) return qPow(2, n);
    int d1 = leaf1 - node, d2 = leaf2 - node;
    if(d1 == d2) return 2 * qPow(2, node) % mod;
    int diff = d1 > d2 ? d1 - d2 : d2 - d1;
    return (qPow(2, diff) + qPow(2, diff - 1)) % mod * qPow(2, node) % mod;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {}), cc = 0, node = leaf1 = leaf2 = -1;
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cout << solve() << "\n";
    }
}