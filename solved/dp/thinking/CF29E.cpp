/**
 * @Time : 2025/1/31-2:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF29E 2400 动态规划 bfs
 */
/*
 * 定义dis[v][w]：a到达v同时b到达w的最短路径长度
 * 已知dis[v][w]可以转移到 dis[nv][nw] 其中nv是v的相邻结点，nw是w的相邻结点 且nv != nw
 * 就是一个bfs 但是要枚举nv和nw，并且状态有二维 时间复杂度是n^4
 * 如果将同时走 拆分为两个步骤 让a先选一个结点走 然后b再选一个结点走 b不可以走a选的位置
 * dis[v][w][0/1]：
 * 0表示a选了结点v，但b没选仍然在w
 * 1表示a已经选了结点v，b选了结点w，w != v
 * 转移方程dis[v][w][1] -> dis[nv][w][0], dis[v][w][0] -> dis[v][nw][1]
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 500 + 5, M = 2 * N;
int n, m, dis[N][N][2], infos[N][N][2][2];
vector<int> graph[N];

int bfs() {
    queue<vector<int>> queue;
    dis[1][n][1] = 1, queue.push({1, n, 1});
    while(!queue.empty()) {
        vector<int> cur = queue.front(); queue.pop();
        int v = cur[0], w = cur[1], f = cur[2];
        if(f == 1) {
            for(int nv : graph[v]) {
                if(dis[nv][w][0] != 0) continue;
                dis[nv][w][0] = dis[v][w][f] + 1;
                queue.push({nv, w, 0});
                infos[nv][w][0][0] = v, infos[nv][w][0][1] = w;
            }
        } else {
            for(int nw : graph[w]) {
                if(nw == v || dis[v][nw][1] != 0) continue;
                dis[v][nw][1] = dis[v][w][f] + 1;
                queue.push({v, nw, 1});
                infos[v][nw][1][0] = v, infos[v][nw][1][1] = w;
                if(v == n && nw == 1) return dis[v][nw][1] / 2;
            }
        }
    }
    return -1;
}

void solve() {
    int step = bfs();
    cout << step << "\n";
    if(step == -1) return;
    vector<int> p1 = {n}, p2 = {1};
    for(int i = 1, cv = n, cw = 1, f = 1; i <= step * 2; i++) {
        int pv = infos[cv][cw][f][0], pw = infos[cv][cw][f][1];
        cv = pv, cw = pw;
        if(f == 1) p2.push_back(cw); // f为1 是b选择的那一次 所以将cw添加到其路径中
        else p1.push_back(cv);
        f = (f + 1) % 2;
    }
    for(int i = p1.size() - 1; i >= 0; i--)
        cout << p1[i] << " ";
    cout << "\n";
    for(int i = p2.size() - 1; i >= 0; i--)
        cout << p2[i] << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> m;
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
};