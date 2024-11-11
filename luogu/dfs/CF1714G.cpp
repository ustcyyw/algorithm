/**
 * @Time : 2024/6/7-10:18 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1714G dfs 回溯 二分
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, MV = 1e9;
typedef long long ll;
int T, n, ans[N];
vector<vector<vector<int>>> graph;

void dfs(int v, ll aSum, vector<ll>& sum) {
    if(v != 1) {
        auto it = upper_bound(sum.begin(), sum.end(), aSum);
        ans[v] = (--it) - sum.begin();
    }
    for(auto& edge : graph[v]) {
        int w = edge[0], a = edge[1], b = edge[2];
        sum.push_back(sum.back() + b);
        dfs(w, aSum + a, sum);
        sum.pop_back();
    }
}

void solve() {
    vector<ll> sum(1, 0ll);
    dfs(1, 0, sum);
    for(int i = 2; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {});
        for(int i = 2, p, a, b; i <= n; i++) {
            cin >> p >> a >> b;
            graph[p].push_back({i, a, b});
        }
        solve();
    }
};