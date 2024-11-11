/**
 * @Time : 2024/11/7-3:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1914F 思维 结论
 */
/*
  * 1.如果某个子数结点数目 > 其它所有的总和 其它的都拿来和这个最多的配对
  * 这个最多的内部依然还需要考虑如何分配
  * 2.否则 总是可以通过调整 尽可能地完成均匀分配
  *
  * 对于1的情况 将其他子树的结点拿来均匀分配
  * 将其它子树结点拿来分配的时候 首先拿出其中一个结点（如果有的话）和最大子树的头结点v匹配
  * 剩下的结点就可以当作等效的v的子树，并且不是最大子树 重复开始的判断过程
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, cnt[N], maxC[N], idx[N], ans;
vector<vector<int>> graph;

void dfs1(int v, int father) {
    cnt[v] = 1;
    for(int w : graph[v]) {
        if(w  == father) continue;
        dfs1(w, v);
        cnt[v] += cnt[w];
        if(cnt[w] > maxC[v]) maxC[v] = cnt[w], idx[v] = w;
    }
}

void dfs2(int v, int total) {
    if(graph[v].empty()) return;
    int other = cnt[v] - 1 - maxC[v] + total; // 计算除最大子树外 还有多少个结点可用
    if(other >= maxC[v]) {
        ans += (total + cnt[v] - 1) / 2;
        return;
    }
    if(other > 0) ans++; // 表示other中拿出一个和最多结点的子树的头结点进行一组配对
    dfs2(idx[v], max(other - 1, 0)); // 注意从别的子树拿过来补充的结点 不能为负
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        ans = 0, graph.assign(n + 1, {}), fill(maxC, maxC + n + 1, 0);
        for(int i = 2, father; i <= n; i++) {
            cin >> father;
            graph[father].push_back(i);
        }
        dfs1(1, -1);
        dfs2(1, 0);
        cout << ans << "\n";
    }
};