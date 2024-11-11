/**
 * @Time : 2024/7/3-5:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1399E1 贪心
 */
 /*
  * 每次都找能使总和降低最多的边 注意每条边都最终连着确定数量的叶子结点cnt
  * 每次操作降低的总和为 cnt * (val - val / 2)
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, s, val[N], cnt[N], sum;
vector<vector<vector<int>>> graph;

ll cal_diff(int i) {
    ll c = cnt[i], v = val[i];
    return (v - v / 2) * c;
}

struct cmp{
    bool operator()(int& a, int& b){
        return cal_diff(a) < cal_diff(b);
    }
};
priority_queue<int, vector<int>, cmp> pq;

int dfs(int v, int f, ll curS) {
    if(f != -1 && graph[v].size() == 1) {
        sum += curS;
        return 1;
    }
    int total = 0;
    for(auto& p : graph[v]) {
        int w = p[0], id = p[1];
        if(w == f) continue;
        int t = dfs(w, v, curS + val[id]);
        total += t, cnt[id] = t;
    }
    return total;
}

void solve() {
    dfs(1, -1, 0);
    pq = {};
    for(int i = 1; i < n; i++)
        pq.push(i);
    int ans = 0;
    while(sum > s) {
        int i = pq.top();
        pq.pop();
        sum -= cal_diff(i), ans++;
        val[i] /= 2, pq.push(i);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        graph.assign(n + 1, {}), sum = 0;
        for(int i = 1, a, b, w; i < n; i++) {
            cin >> a >> b >> w;
            val[i] = w;
            graph[a].push_back({b, i}), graph[b].push_back({a, i});
        }
        solve();
    }
};