/**
 * @Time : 2024/5/20-10:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1213G 离线算法 + 并查集
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
ll T, n, m, ans[N], id[N], sz[N];
vector<vector<int>> query, edge;

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

ll connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return 0;
    ll cnt = sz[p] * sz[q];
    id[p] = q, sz[q] += sz[p];
    return cnt;
}

void solve() {
    sort(edge.begin(), edge.end()), sort(query.begin(), query.end());
    ll sum = 0;
    for(int j = 0, i = 0; j < m; j++) {
        int w = query[j][0], idx = query[j][1];
        while(i < n - 1 && edge[i][0] <= w) {
            int p = edge[i][1], q = edge[i][2];
            sum += connect(p, q);
            i++;
        }
        ans[idx] = sum;
    }
    for(int i = 0; i < m; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        id[i] = i, sz[i] = 1;
    for(int i = 1, a, b, w; i < n; i++) {
        cin >> a >> b >> w;
        edge.push_back({w, a, b});
    }
    for(int i = 0, w; i < m; i++) {
        cin >> w;
        query.push_back({w, i});
    }
    solve();
};