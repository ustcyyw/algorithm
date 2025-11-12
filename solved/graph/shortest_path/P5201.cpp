/**
 * @Time : 2023/5/11-10:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int n, m, t, marked[N], dist[N], path[N], cnt[N], max_val = 1e9;
vector<vector<vector<int>>> graph;

struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) {
        int temp = dist[a[0]] + a[2] - dist[b[0]] - b[2];
        return temp >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};

void dijkstra(int s) {
    fill(dist, dist + n + 1, max_val);
    fill(marked, marked + n + 1, 0);
    fill(path, path + n + 1, -1);
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    dist[s] = 0;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for(auto& edge : graph[v]) {
            int w = edge[1], cost = edge[2];
            if(dist[w] > dist[v] + cost) {
                dist[w] = dist[v] + cost;
                path[w] = v;
                pq.push(edge);
            } else if(dist[w] == dist[v] + cost && v < path[w]) {
                path[w] = v;
                pq.push(edge);
            }
        }
    };
    relax(1);
    while (pq.size()) {
        vector<int> edge = pq.top(); pq.pop();
        if(!marked[edge[1]]) relax(edge[1]);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    memset(cnt, 0, sizeof(cnt));
    cin >> n >> m >> t;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        cnt[i] = num;
    }
    graph.assign(n + 1, {});
    for(int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c;
        graph[a].push_back({a, b, c}), graph[b].push_back({b, a, c});
    }
    dijkstra(1);
    // dfs计算经过结点v到达结点1的牛的数量
    vector<vector<int>> tree(n + 1);
    for(int i = 2; i <= n; i++)
        tree[path[i]].push_back(i);
    function<int(int)> dfs = [&](int x) -> int {
        for(int w : tree[x])
            cnt[x] += dfs( w);
        return cnt[x];
    };
    dfs(1);
    long long ans = 0;
    for(int i = 2; i <= n; i++)
        ans = max(ans, (long long)(dist[i] - t) * cnt[i]);
    cout << ans << endl;
}