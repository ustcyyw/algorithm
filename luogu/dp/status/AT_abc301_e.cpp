/**
 * @Time : 2023/8/23-9:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int K = 305, dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
int n, m, T, s, e, num;

vector<string> grid;
unordered_map<int, int> k_id; // key -> 猴子id;
vector<vector<int>> dis, cache;
void min_steps(int start){
    int step = 1;
    queue<int> queue; unordered_set<int> marked;
    queue.push(start); marked.insert(start);
    while (!queue.empty() && step <= T) {
        int sz = queue.size();
        for(int k = 0; k < sz; k++) {
            int key = queue.front();
            queue.pop();
            int x = key / K, y = key % K;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                int nk = nx * K + ny;
                if(marked.count(nk) || grid[nx][ny] == '#') continue;
                if(k_id.count(nk)) {
                    int i1 = k_id[start], i2 = k_id[nk];
                    dis[i1][i2] = dis[i2][i1] = step;
                }
                queue.push(nk); marked.insert(nk);
            }
        }
        step++;
    }
}

// 最后到达猴子k，并且猴子状态为status的最短距离
int dfs(int status, int k) {
    if(cache[status][k] != INT_MIN) return cache[status][k];
    int res = INT_MAX, ns = status ^ (1 << k);
    for(int i = 0; i < num; i++) { // 枚举上一个到达的猴子
        if(!((1 << i) & ns) || dis[i][k] == -1) continue;
        if(dfs(ns, i) != -1)
            res = min(res, dfs(ns, i) + dis[i][k]);
    }
    cache[status][k] = res > T ? -1 : res;
    return cache[status][k];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> T;
    string line;
    for(int i = 1; i <= n; i++) {
        cin >> line;
        grid.push_back(line);
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int key = i * K + j; char c = grid[i][j];
            if(c == 'S') s = key;
            if(c == 'G') e = key;
            if(c == 'o') k_id[key] = (int)k_id.size();
        }
    }
    k_id[s] = (int)k_id.size(); k_id[e] = (int)k_id.size();
    int sz = (int)k_id.size(); num = sz - 2; // num 是猴子数量， 也恰好是起点的编号
    // 预处理猴子与起点终点的距离
    dis = vector(sz, vector(sz, -1));
    for(auto& pair : k_id)
        min_steps(pair.first);
    if(dis[sz - 1][sz - 2] > T || dis[sz - 1][sz - 2] == -1) {
        cout << -1 << endl;
        return 0;
    }
    int full = (1 << num) - 1;
    cache = vector(full + 1, vector(sz, INT_MIN));
    for(int i = 0; i < num; i++)
        cache[1 << i][i] = dis[num][i];
    int res = 0;
    for(int u = full; u; u = (u - 1) & full) {
        for(int i = 0; i < num; i++) {
            dfs(u, i);
            if(cache[u][i] > 0 && dis[i][sz - 1] != -1 && cache[u][i] + dis[i][sz - 1] <= T)
                res = max(res, __builtin_popcount(u));
        }
    }
    cout << res << endl;
}