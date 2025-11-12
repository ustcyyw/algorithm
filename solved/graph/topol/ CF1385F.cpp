/**
 * @Time : 2024/7/2-3:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1385F 拓扑排序 + 模拟
 */
 /*
  * 肯定是从外层开始 逐渐删除
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, k, degree[N], marked[N];
vector<vector<int>> graph;

int solve() {
    if(k == 1) return n - 1;
    unordered_map<int, int> map; // 记录某个结点的叶子结点数目
    queue<int> queue; // 记录要删除k个叶子结点的父亲结点编号
    for(int i = 1; i <= n; i++) {
        if(degree[i] != 1) continue;
        marked[i] = 1;
        int w = graph[i][0];
        if(++map[w] == k && !marked[w]) queue.push(w);
    }
    int ans = 0;
    while(!queue.empty()) {
        int v = queue.front(), t = map[v] / k;
        ans += t, map[v] -= t * k, degree[v] -= t * k;
        if(map[v] == 0 && degree[v] == 1) { // v已经没有叶子结点了 自己变成了叶子结点
            marked[v] = 1;
            for(int w : graph[v]) {
                if(marked[w]) continue;
                if(++map[w] == k) queue.push(w);
            }
        }
        queue.pop();
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        graph.assign(n + 1, {});
        fill(degree, degree + n + 1, 0), fill(marked, marked + n + 1, 0);
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
            degree[v]++, degree[w]++;
        }
        cout << solve() << "\n";
    }
};