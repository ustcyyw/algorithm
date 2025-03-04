/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 有先后次序 容易想到拓扑排序
  * 又要求最终答案字典序最小 会想到优先将小的值赋值给编号小的结点
  * 但是这个操作有后效性 比如 4 -> 2, 5 -> 1
  * 按拓扑序直接这样贪心会将结点4赋值为1 结点2赋值为2 结点5赋值为3 结点1赋值为4
  * 但是显然应该先将结点5赋值为1，然后结点1赋值为2
  *
  * 逆向思维 保持拓扑排序的框架不变 从反图中考虑
  * 入度为0的结点 就是原图中 出度为0的点
  * 这些结点中的一个 一定会被分配值n 反证法
  * 假设这些结点都没有赋值n，那么这些结点的值[1, n-1], 这些结点的前置结点中就有一个点被赋予n
  * 被赋予n的结点排在了更前面 无法满足值的相对大小 与 拓扑序相对顺序的要求 矛盾了
  * 那既然n一定要给反图中入度为0的结点 为了让字典序最小 就赋值给编号最大的那个即可
  * 在返图中拓扑排序 并优先给编号大的结点赋大的值即可
  * 这样赋值 在原图中没有后效性
  * 因为原图中这个点之后的结点 已经被赋予更大的值了 不影响次序和赋值的要求
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, P = 13331;
int n, m, degree[N], ans[N];
vector<int> graph[N];

void topol_bfs() {
    int cur = n;
    priority_queue<int> pq;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) pq.push(i);
    while (pq.size()) {
        int v = pq.top(); pq.pop();
        ans[v] = cur--;
        for(int w : graph[v])
            if(--degree[w] == 0) pq.push(w);
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        graph[b].push_back(a), degree[a]++;
    }
    topol_bfs();
}