/**
 * @Time : 2025/6/10-15:42
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2117G 2009 并查集 离线思想
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 998244353;
int T, n, m, id[N], minV[N], maxV[N];
vector<vector<int>> edges;

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

void connect(int p, int q, int val) {
    p = find(p), q = find(q);
    if(p == q) return;
    id[p] = q;
    minV[q] = min({minV[q], minV[p], val}), maxV[q] = max({maxV[q], maxV[p], val});
}

void solve() {
    int ans = INT_MAX;
    for(auto& edge : edges) {
        int val = edge[0], p = edge[1], q = edge[2];
        connect(p, q, val);
        int t1 = find(1), tn = find(n);
        if(t1 == tn && minV[t1] != INT_MAX)
            ans = min(minV[t1] + val, ans);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        edges = {};
        for(int i = 1; i <= n; i++)
            id[i] = i;
        fill(minV, minV + n + 1, INT_MAX), fill(maxV, maxV + n + 1, INT_MIN);
        for(int i = 1, a, b, w; i <= m; i++) {
            cin >> a >> b >> w;
            edges.push_back({w, a, b});
        }
        sort(edges.begin(), edges.end());
        solve();
    }
}