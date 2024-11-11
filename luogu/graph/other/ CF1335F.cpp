/**
 * @Time : 2024/6/23-4:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1335F 图论 拓扑排序 bfs 贪心
 */
 /*
  * 根据题目的意思 机器人是可以一直走的 那么他们一定在一个环里面走
  * 并且任意时间点都不能占到同一个位置 因此最终机器人们是刚好能填满每一环
  * 所以放置机器人的数量最大值 就是环中元素的个数 所以需要先建图
  * 用拓扑排序将非环元素找出来
  *
  * 在此基础之上 来找出发点是黑色的机器人最大数量 记环的元素个数有cc个
  * 能占满整个环 就要求到达环中某一个点的机器人的时刻刚好有cc个值
  * 这里的值是指cc取mod后的不同值 因为取mod后相同的值说明他们套圈了 还是会在同一个时刻到达该点
  * 那么可以逆向来做 任选一个环中的点 在反图中bfs 标记它到达黑色点的时间
  * 统计到达黑色点时间对cc取mod后有多少个值
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int T, n, m, cnt1, cnt2, color[N];
vector<int> degree, marked;
vector<vector<int>> graph, rg;
string nums[N], s[N];

void build() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int v = i * m + j, w = -1;
            color[v] = nums[i][j] - '0';
            char c = s[i][j];
            if(c == 'L') w = i * m + j - 1;
            else if(c == 'R') w = i * m + j + 1;
            else if(c == 'U') w = (i - 1) * m + j;
            else w = (i + 1) * m + j;
            graph[v].push_back(w), rg[w].push_back(v);
            degree[w]++;
        }
    }
}

void find_cycle() {
    queue<int> queue;
    for(int i = 0; i < n * m; i++)
        if(degree[i] == 0) queue.push(i), marked[i] = 1;
    while(!queue.empty()) {
        int v = queue.front();
        for(int w : graph[v]) {
            if(marked[w]) continue;
            if(--degree[w] == 0) queue.push(w), marked[w] = 1;
        }
        queue.pop();
    }
}

int dfs(int v) {
    marked[v] = 2; // 标记其为2 表示是环中的元素
    for(int w : graph[v])
        if(!marked[w]) return 1 + dfs(w);
    return 1;
}

int bfs(int start, int cc) {
    vector<int> pick(cc, 0);
    int step = 0;
    queue<int> queue;
    queue.push(start);
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            int v = queue.front();
            if(color[v] == 0) pick[step % cc] = 1;
            for(int w : rg[v]) {
                // 由于每个点的出度是1 不会存在一个点在两个环中的情况 所以判断已访问只需要和起点比较即可
                if(w != start) queue.push(w);
            }
            queue.pop();
        }
        step++;
    }
    return accumulate(pick.begin(), pick.end(), 0);
}

void solve() {
    find_cycle();
    for(int i = 0; i < n * m; i++) {
        if(marked[i]) continue;
        int cc = dfs(i);
        cnt1 += cc;
        cnt2 += bfs(i, cc);
    }
    cout << cnt1 << " " << cnt2 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        graph.assign(n * m, {}), rg.assign(n * m, {});
        degree.assign(n * m, 0), marked.assign(n * m, 0);;
        cnt1 = cnt2 = 0;
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        for(int i = 0; i < n; i++)
            cin >> s[i];
        build();
        solve();
    }
};