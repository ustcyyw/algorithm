/**
 * @Time : 2024/9/3-1:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1790F 根号分治
 */
/*
  * 一个结论： 在一棵n个结点的树中 任意选择x个结点 所有被选择结点点对之间的最小距离的量级不超过n/x
  * 设想一种极端情况，n个结点的树退化为一条链 均匀分别x个点能让最小距离最大 这个最小距离的量级就是 n / x
  * 而其它情况下 树比链更为紧凑，因此最小距离更不会超过 n/x 的量级
  *
  * 每次操作使一个点变成黑色点 只有它可能会变成其它黑点新的最短距离
  * 所以一个暴力的做法就是每次操作的点为起点进行搜索 找到可能的最短距离
  * （因为是树 bfs或者dfs走出来的路线都是最短路线）
  *
  * 在bfs的时候如果距离已经超过记录着的最小距离 那么继续搜索不会改变答案 有效减枝1
  *
  * 假设被改变的点是v，另外一个点为w
  * 用dis[i]: 表示结点i到黑点的最短距离 如果i是黑点 那么dis[i] = 0
  * 如果dis[w] <= d(v,w) 说明确定dis[w]值的那个黑点k只可能有以下两种情况：
  * 1. k 在 v -> w 的路径上
  * 2. k 在 w 的子树中
  * 并且显然对于w子树中结点的dis值只可能会由k确定，而绝对不会由v确定 因此搜索终止
  * 因此 可以有效减枝2
  *
  * 然后分析时间复杂度 根号分治的思想
  * 前sqrt(n)个点的操作 即便每次操作都搜索完所有点 总时间复杂度为n * sqrt(n)
  * 后sqrt(n)个点的操作 根据一开始说明的结论 最小距离的量级为 n / sqrt(n) = sqrt(n)
  * 那么对于dis[i]可更新的值的范围从1到sqrt(n) 共有n个点可能会被更新
  * 因此整个dis[i]数组的更新次数仅为 n * sqrt(n)
  * 所以 整体的时间复杂度是 n * sqrt(n)
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
int T, n, c0, blacks[N], dis[N], res;
vector<vector<int>> graph;

// s表示当前操作被更改的点
void bfs(int s) {
    queue<int> q;
    q.push(s), dis[s] = 0; // s本身就是黑点 那么s到黑点的最短距离就是0
    while(!q.empty()) {
        int sz = q.size();
        while(sz-- > 0) {
            int v = q.front(); q.pop();
            if(dis[v] >= res) continue; // 减枝1 由v延伸出去的距离 >= 最小距离 再继续搜索不会更新答案
            for(int w : graph[v]) {
                // v的下一个子结点是w，w到最近黑点的距离可能是w到v，然后v到该黑点 因而距离可能是dis[v] + 1
                if(dis[v] + 1 >= dis[w]) continue; // 减枝2 该距离大于w到另外黑点的距离
                dis[w] = dis[v] + 1, q.push(w);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> c0;
        for(int i = 1; i < n; i++)
            cin >> blacks[i];
        graph.assign(n + 1, {});
        fill(dis, dis + n + 1, N), res = N + 10;
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        bfs(c0); // c0一开始就是黑点
        for(int i = 1; i < n; i++) {
            int v = blacks[i];
            // v现在变成黑点了 那么可能的最小距离黑点对中一个点可能是v，该距离就是dis[v]
            res = min(res, dis[v]);
            bfs(v);
            cout << res << " ";
        }
        cout << "\n";
    }
};