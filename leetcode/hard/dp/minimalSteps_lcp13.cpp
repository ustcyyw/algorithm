/**
 * @Time : 2023/8/22-2:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
const int T = 101, dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

class Solution {
public:
    int n, m, s, t, num; // num是机关的数目
    vector<string> grid;
    vector<int> map; // 机关编号 -> 机关的key
    vector<vector<int>> cache, m_dis; // m_dis 是机关（起点）之间经过石头的最短距离
    unordered_map<int, unordered_map<int, int>> dis; // dis[i][j] i -> j的最短路径
    int minimalSteps(vector<string>& grid) {
        this->grid = grid;
        n = grid.size(), m = grid[0].size();
        unordered_set<int> machine, stone;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int key = i * T + j;
                if(grid[i][j] == 'S') s = key;
                if(grid[i][j] == 'T') t = key;
                if(grid[i][j] == 'O') stone.insert(key);
                if(grid[i][j] == 'M') machine.insert(key), map.push_back(key);
            }
        }
        num = map.size();
        if(num == 0) { // 没有任何机关 直接走的情况
            min_steps(s, {t});
            return dis[s][t] == 0 ? -1 : dis[s][t];
        }
        min_steps(s, stone), min_steps(t, machine); // 起点到各个石头，各个机关到终点的距离计算
        for(int pos : machine)
            min_steps(pos, stone); // 各个机关，石头之间的距离计算
        // 预处理机关之间经过石头的最短距离，起点与机关之间的最短距离
        map.push_back(s);
        m_dis = vector(map.size(), vector(map.size(), 0));
        for(int i = 0; i < map.size(); i++) {
            for(int j = i + 1; j < map.size(); j++) {
                int pk = map[i], ck = map[j], min_val = INT_MAX;
                for(int sk : stone) {
                    if(dis[pk][sk] != 0 && dis[sk][ck] != 0) // 不为0才表示可达
                        min_val = min(min_val, dis[pk][sk] + dis[sk][ck]);
                }
                if(min_val == INT_MAX) return -1;
                m_dis[i][j] = m_dis[j][i] = min_val;
            }
        }
        int full = (1 << num) - 1;
        cache = vector(full + 1, vector(num, -1));
        for(int i = 0; i < num; i++) // 起点到各个机关的距离计算
            cache[1 << i][i] = m_dis[i][(int)map.size() - 1];
        // 枚举最后到达的机关
        int res = INT_MAX;
        for(int i = 0; i < num; i++) {
            int d = dfs(full, i);
            if(d != 0 && dis[map[i]][t] != 0)
                res = min(res, dfs(full, i) + dis[map[i]][t]);
        }
        return res == INT_MAX ? -1 : res;
    }

    // 最后到达机关k，并且机关状态为status的最短距离
    int dfs(int status, int k) {
        if(cache[status][k] != -1) return cache[status][k];
        int res = INT_MAX;
        int ts = status ^ (1 << k);
        for(int i = 0; i < num; i++) { // 枚举上一个到达的机关
            int temp = 1 << i;
            if(!(temp & ts) || m_dis[i][k] == 0) continue;
            res = min(res, dfs(ts, i) + m_dis[i][k]);
        }
        cache[status][k] = res == INT_MAX ? 0 : res;
        return cache[status][k];
    }

    // s是起点 ends是目标点集合 求最短距离
    void min_steps(int s, unordered_set<int> ends){
        int step = 1;
        queue<int> queue; unordered_set<int> marked;
        queue.push(s); marked.insert(s);
        while (!queue.empty()) {
            int sz = queue.size();
            for(int k = 0; k < sz; k++) {
                int key = queue.front();
                queue.pop();
                int x = key / T, y = key % T;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                    int nk = nx * T + ny;
                    if(marked.count(nk) || grid[nx][ny] == '#') continue;
                    if(ends.count(nk)) dis[s][nk] = dis[nk][s] = step;
                    queue.push(nk); marked.insert(nk);
                }
            }
            step++;
        }
    }
};