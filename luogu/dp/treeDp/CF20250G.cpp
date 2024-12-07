/**
 * @Time : 2024/12/6-9:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF20250G 1985 动态规划 树型dp
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, ans;
vector<vector<int>> graph;

int dfs(int v, int f) {
    if(graph[v].size() == 1 && f != -1) return 0;
    ans = max(ans, (int)graph[v].size()); // 只将v删除作为路径的一个端点时 能贡献的分量
    int c1 = -1, c2 = -1;
    for(int w : graph[v]) {
        if(w == f) continue;
        int t = dfs(w, v);
        if(t > c1) c2 = c1, c1 = t;
        else if(t > c2) c2 = t;
    }
    // 可以选择两个子结点（这两个子结点是被删除的单路径的端点）和自己一起删除 这就完成了一条路径
    // 这种情况选择的两个子结点肯定要多于1个分量 不然将其留下 把v删了 它也能成为一个分量
    if(c2 > 1) ans = max(ans, (int)graph[v].size() - 2 + c1 + c2);
    if(c1 > 1) ans = max(ans,  (int)graph[v].size() - 1 + c1);
    // 选择删除一个子结点 那就是一个简单路径 或者只删除自己 也是相当这个结点作为简单路径的一个端点
    // 二者都用于在祖先结点中构建完整路径的一部分 因为交个祖先去判断如何选择 所以度数要减去f带来的1
    return max(graph[v].size() - 1, graph[v].size() - 2 + c1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        ans = -1, graph.assign(n + 1, {});
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(1, -1);
        cout << ans << "\n";
    };
};