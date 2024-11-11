/**
 * @Time : 2024/9/2-5:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1790G 思维题 模拟实现
 */
/*
  * 任何一步走到非特殊点 都会导致流程终止
  *
  * 如果选定了其中一个棋子是最终到达终点的棋子s
  * 那么过程中就尽量通过其它棋子的操作让s来走向1 并且应该走最短路线
  * 考虑选什么棋子
  * 一定是通过特殊点能连接到终点1的棋子
  * 并且应该是路程最短的棋子
  *
  * 如果某个棋子能走到至少有两个相邻特殊点 那这个棋子就可以通过折反走来提供其它棋子前进
  *
  * 有一些特殊的情况可以单独讨论
  * 1. 如果有有一个棋子离终点1只有一步路 那就直接走即可
  * 2. 第一个情况不存在的情况，如果只有1个棋子 肯定没法完成
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
// pos记录棋子的初始位置， spe记录特殊点的位置
int T, n, m, p, b, pos[N], spe[N], len[N];
vector<vector<int>> graph;
vector<int> id, sz;

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return;
    id[p] = q, sz[q] += sz[p];
}

// 找到某个棋子0步或者1步能到达的最大特殊点连通块
int get_cnt(int p) {
    if(spe[p]) {
        int t = sz[find(p)];
        return t == 1 ? 0 : t; // 如果棋子就在特殊点上 并且该特殊点连通块就1个点 那么是无法移动的 等价于0
    }
    int ans = -1;
    for(int w : graph[p])
        ans = max(ans, sz[find(w)]);
    return ans;
}

void bfs() {
    queue<int> queue;
    int step = 1;
    queue.push(1);
    vector<int> marked(n + 1, 0);
    while(!queue.empty()) {
        int t = queue.size();
        for(int i = 0; i < t; i++) {
            int v = queue.front(); queue.pop();
            for(int w : graph[v]) {
                if(marked[w]) continue;
                if(pos[w] && len[w] > step) len[w] = step;
                if(spe[w]) queue.push(w), marked[w] = 1;
            }
        }
        step++;
    }
}

bool solve() {
    if(pos[1]) return true;
    bfs();
    // 找到能到达终点1的最短路径的棋子
    int minL = INT_MAX, s = -1;
    for(int i = 1; i <= n; i++) {
        if(len[i] < minL)
            minL = len[i], s = i;
    }
    if(minL <= 1) return true; // 开局一步就有棋子可以走到终点1的情况
    // 压根没有棋子可以通过特殊点到1 或者 只有一个棋子 并且一步走不到1的情况
    if(minL == INT_MAX || p == 1) return false;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(i == s || !pos[i]) continue;
        int ct = get_cnt(i);
        if(ct > 1) return true; // 有一个另外的棋子可用于反复走的情况
        cnt += ct;
    }
    return 1 + cnt >= minL;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> p >> b;
        graph.assign(n + 1, {});
        fill(pos, pos + n + 1, 0), fill(spe, spe + n + 1, 0);
        fill(len, len + n + 1, INT_MAX);
        for(int i = 1, t; i <= p; i++) {
            cin >> t;
            pos[t] = 1;
        }
        for(int i = 1, t; i <= b; i++) {
            cin >> t;
            spe[t] = 1;
        }
        id.assign(n + 1, 0), sz.assign(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            id[i] = i;
            if(spe[i]) sz[i] = 1;
        }
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            if(spe[v] && spe[w]) connect(v, w); // 两个点都是红色才连通
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};