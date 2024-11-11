/**
 * @Time : 2024/7/3-9:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1399E2 贪心
 */
 /*
  * 大体思路和简单版本 CF1399E1 是一致的。看怎么尽可能减少权重和
  * 只不过本题有耗费1的边和耗费2的边 分别极为a类边和b类边
  * 如何确定性价比呢
  * 1.如果两个边类型相同，都是a类或者b类 那么参考easy版本的比较即可
  * 2.如果一条边是a类，另外一条是b类
  * 那么应该使用两次a类边去和b类比 看看谁能削减得多
  * 注意是两次a类边，而不是两条a类边，因为使用完削减最多的a1边之后
  * 下一次可能还是a1边削减最多，也可能是a2边更多 所以这里也要做选择
  *
  * 此外 还有一种特殊情况
  * 就是b类边一次 比 a类边2次削减要多 但是此时只需要一次a类边削减就能达到目标
  * 那么当然直接使用一次a类边的削减
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, s, val[N], cnt[N], sum, cost[N];
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
priority_queue<int, vector<int>, cmp> pq1, pq2;

ll cal_two() {
    int i = pq1.top(); pq1.pop();
    ll t1 = pq1.empty() ? -1 : cal_diff(pq1.top());
    ll c = cnt[i], v = val[i] / 2, t2 = (v - v / 2) * c;
    ll ans = cal_diff(i) + max(t1, t2);
    pq1.push(i);
    return ans;
}

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
    pq1 = {}, pq2 = {};
    for(int i = 1; i < n; i++) {
        if(cost[i] == 1) pq1.push(i);
        else pq2.push(i);
    }
    ll ans = 0;
    while(sum > s) {
        if(!pq1.empty() && sum - cal_diff(pq1.top()) <= s) {
            ans++;
            break;
        }
        if(pq2.empty() || (!pq1.empty() && cal_two() >= cal_diff(pq2.top()))) {
            int i = pq1.top(); pq1.pop();
            sum -= cal_diff(i), ans += cost[i];
            val[i] /= 2, pq1.push(i);
        } else {
            int i = pq2.top(); pq2.pop();
            sum -= cal_diff(i), ans += cost[i];
            val[i] /= 2, pq2.push(i);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        graph.assign(n + 1, {}), sum = 0;
        for(int i = 1, a, b, w, c; i < n; i++) {
            cin >> a >> b >> w >> c;
            val[i] = w, cost[i] = c;
            graph[a].push_back({b, i}), graph[b].push_back({a, i});
        }
        solve();
    }
};