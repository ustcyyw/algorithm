/**
 * @Time : 2025/3/31-9:25 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF962E 2400 tarjan 点双连通分量 （看答案）
 */
 /*
  * 一个简单环 点的数量 = 边的数量
  * 在简单环上再加一条边，必然将这个环分为两部分 就会有两个新的环 以及原本的环
  * 就使得所有边都在两个环中
  * 增加更多的边 只会让环更多 让这些边属于更多的环
  * 因此 一个环中边的数量 > 点的数量 那么这个环中任意边都至少属于两个环
  *
  * 如果两个环仅由一个公共点连接，那么这两个环互不影响，即点双两两互不影响
  * 有公共边的两个环 就是 环中边的数量 > 点的数量 的情况
  * 因此要找的答案最多由一个公共点连接，也就是说要找点双连通分量（也就是要找到割点）
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 15, M = 30;
int n, m, edges[N][2], idx, st[N], dfn[N], low[N];
// id用来标识当前点双分量; nodeC[i], edgeC[i]: 分量i中的点数和边数；edgeId[i]：第i边属于哪个点双分量
int id, nodeC[N], edgeC[N], edgeId[N];
vector<int> graph[N];
set<int> sts[N]; // sts[i]:结点i属于哪个点双分量，因为割点可能属于多个点双 所以用set存储

void tarjan() {
    int time = 1;
    function<void(int, int)> dfs = [&](int v, int f) -> void {
        int cnt = 0;
        dfn[v] = low[v] = time++;
        st[idx++] = v;
        for(int w : graph[v]) {
            if(dfn[w] == -1) {
                cnt++, dfs(w, v);
                low[v] = min(low[v], low[w]);
                if(low[w] >= dfn[v]) {
                    id++;
                    // 注意 idx - 1才是栈顶索引，st[idx] == w 说明w刚好出栈 并且割点没有出栈
                    while(st[idx] != w) {
                        int cur = st[--idx];
                        sts[cur].insert(id), nodeC[id]++;
                    }
                    sts[v].insert(id), nodeC[id]++;
                }
            } else if(w != f)
                low[v] = min(low[v], dfn[w]);
        }
        // if(cnt == 0 && f == -1) groups.push_back({v}); // 特判孤立点 孤立点不会导致环
    };
    for(int i = 1; i <= n; i++) {
        if(dfn[i] == -1) {
            idx = 0; dfs(i, -1);
        }
    }
}
// 检查边 a-b 在哪个点双分量中
int checkGroup(int a, int b) {
    if(sts[a].size() <= sts[b].size()) {
        for(int cid : sts[a]) {
            if(sts[b].count(cid))
                return cid;
        }
    } else {
        for(int cid : sts[b]) {
            if(sts[a].count(cid))
                return cid;
        }
    }
    return -1;
}

void solve() {
    tarjan();
    for(int i = 1; i <= m; i++) {
        int cid = checkGroup(edges[i][0], edges[i][1]);
        edgeId[i] = cid;
        if(cid != -1) edgeC[cid]++;
    }
    vector<int> ans;
    for(int i = 1; i <= m; i++) {
        if(edgeId[i] != -1 && edgeC[edgeId[i]] == nodeC[edgeId[i]])
            ans.push_back(i);
    }
    cout << ans.size() << "\n";
    for(int cid : ans)
        cout << cid << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        edges[i][0] = a, edges[i][1] = b;
        graph[a].push_back(b), graph[b].push_back(a);
    }
    fill(dfn, dfn + n + 1, -1), fill(low, low + n + 1, INT_MAX);
    solve();
}