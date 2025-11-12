/**
 * @Time : 2023/5/10-12:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 105;
int n, m, max_val = 1e9, dist[N], marked[N], path[N];
vector<vector<int>> grid;

void dijkstra(int s) {
    fill(dist, dist + n + 1, max_val);
    fill(path, path + n + 1, -1);
    fill(marked, marked + n + 1, 0);
    dist[s] = 0;
    for(int i = 1; i <= n; i++) { // 每次将一个点添加到最短路径树中 共添加n个点
        int val = max_val, v = -1;
        for(int j = 0; j < n; j++) { // 找到当前距离最小的点 就是这一轮添加到最短路径树中的点
            if(marked[j]) continue;
            val = min(val, dist[j]);
            if(dist[j] == val) v = j;
        }
        marked[v] = true;
        for(int w = 1; w <= n; w++) { // 放缩
            if(!marked[w] && dist[w] > dist[v] + grid[v][w]) {
                dist[w] = dist[v] + grid[v][w];
                path[w] = v;
            }
        }
    }
}

vector<int> get_path(int e) {
    vector<int> ans;
    while (e != -1) {
        ans.push_back(e);
        e = path[e];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    grid = vector(n + 1, vector(n + 1, max_val));
    for(int i = 1; i <= n; i++)
        grid[i][i] = 0;
    for(int i = 0, v, w, l; i < m; i++) {
        cin >> v >> w >> l;
        grid[v][w] = grid[w][v] = l;
    }
    dijkstra(1);
    int sp1 = dist[n], ans = -1;
    vector<int> s_path = get_path(n);
    for(int i = 0; i < s_path.size() - 1; i++) {
        int v = s_path[i], w = s_path[i + 1];
        grid[v][w] = grid[w][v] = 2 * grid[v][w];
        dijkstra(1);
        ans = max(ans, dist[n] - sp1);
        grid[v][w] = grid[w][v] = grid[v][w] / 2;
    }
    cout << ans << endl;
}