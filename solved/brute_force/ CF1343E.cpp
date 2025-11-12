/**
 * @Time : 2024/6/25-12:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1343E 枚举 bfs 贪心
 */
/*
 * 如果只是问两个点最短路径 直接bfs找到无权图最短路径 然后将较小值依次安排
 * 但是变成3个点 a -> b -> c
 * 由于是无向图 a -> b 的距离和 b -> a 一致
 * 因此等价于从b到a和到c的最短路径和
 *
 * 分别使用bfs找b到a、c的最短路 然后分配边权 不一定是最优的
 * 因为有可能b先走到一个点d 然后从d分别走到a和b  b -> d -> a, b -> d -> c
 * 到d的路径权重很小 虽然这样安排到a和c不一定是bfs意义下的最短路 但是总和更小了 比 b->a, b->c分别安排求和更小
 *
 * 不确定d怎么选取 可以枚举每个点为d 计算bfs意义下 d到a和c的最短路径
 * 注意如果当前枚举的d可能是非常差的方案
 * 比如所给的图是 b - a - c - d1 这样的，从b到d1绕远了
 * 但是也会枚举到b或者a就是那个中间点d的正确答案
 * 所以某一个d是差方案 也不会影响最终正确性
 * 另外直接找b到a、c最短路的那种方案 就是枚举到d=b的特殊方案。
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, m, a, b, c, val[N], b_dis[N], a_dis[N], c_dis[N];
ll sum[N];
vector<bool> marked;
vector<vector<int>> graph;

void bfs(int s, int* dis) {
    marked.assign(n + 1, false);
    queue<int> queue;
    queue.push(s), marked[s] = true;
    int step = 0;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            int v = queue.front();
            dis[v] = step;
            for(int w : graph[v])
                if(!marked[w]) marked[w] = true, queue.push(w);
            queue.pop();
        }
        step++;
    }
}

void solve() {
    for(int i = 1; i <= m; i++)
        sum[i] = sum[i - 1] + val[i];
    bfs(b, b_dis), bfs(a, a_dis), bfs(c, c_dis);
    ll ans = LONG_LONG_MAX;
    for(int d = 1; d <= n; d++) {
        int lo = b_dis[d], hi = lo + a_dis[d] + c_dis[d];
        if(hi <= m) {
            ll t = sum[lo] * 2 + sum[hi] - sum[lo];
            ans = min(ans, t);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> a >> b >> c;
        graph.assign(n + 1, {});
        for(int i = 1; i <= m; i++)
            cin >> val[i];
        sort(val + 1, val + m + 1);
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        solve();
    }
};