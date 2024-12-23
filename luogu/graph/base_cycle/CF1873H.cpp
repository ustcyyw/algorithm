/**
 * @Time : 2024/12/22-11:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1873H 1700 基环树 拓扑排序 bfs
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, a, b, degree[N], cycle[N];
vector<vector<int>> graph;


void topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 1) queue.push(i);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        cycle[v] = 0;
        for(int w : graph[v]) {
            if(--degree[w] == 1)
                queue.push(w);
        }
    }
}

vector<int> bfs(int s, int& mid) {
    vector<int> marked(n + 1, 0), dis(n + 1, 0);
    queue<int> queue;
    marked[s] = 1, queue.push(s);
    while (!queue.empty()) {
        int sz = queue.size();
        while (sz--) {
            int v = queue.front(); queue.pop();
            for(int w : graph[v]) {
                if(marked[w]) continue;
                marked[w] = 1, queue.push(w);
                dis[w] = dis[v] + 1;
                if(!cycle[v] && cycle[w]) mid = w;
            }
        }
    }
    return dis;
}

// 检查Marce是否能追上Valeriu
bool check() {
    if(a == b) return true;
    topol_bfs();
    if(cycle[b]) return false;
    int midB = 0, midA = 0; // b 不在环上 b与环交点为midB。
    vector<int> disB = bfs(b, midB);
    if(cycle[a]) return disB[a] - disB[midB] <= disB[midB]; // a 在环上的情况
    vector<int> disA = bfs(a, midA);
    return disA[midB] <= disB[midB];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> a >> b;
        graph.assign(n + 1, {});
        fill(degree, degree + n + 1, 0);
        fill(cycle, cycle + n + 1, 1);
        for(int i = 1, v, w; i <= n; i++) {
            cin >> v >> w;
            degree[v]++, degree[w]++;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cout << (!check() ? "YES" : "NO") << "\n";
    }
};