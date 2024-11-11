/**
 * @Time : 2023/5/11-12:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 4e4 + 5;
int n, m, dist[N], marked[N], max_val = 1e9;
vector<vector<char>> grid;
vector<vector<vector<int>>> graph;
struct cmp {
    bool operator()(vector<int>& a, vector<int> b) {
        int v1 = a[0], c1 = a[2], v2 = b[0], c2 = b[2];
        return dist[v1] + c1 >= dist[v2] + c2;
    }
};

void dijkstra(int s) {
    fill(dist, dist + n * m * 4 + 1, max_val);
    memset(marked, 0, sizeof(marked));
    dist[s] = 0;
    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    function<void(int)> relax = [&](int v) {
        marked[v] = true;
        for(auto& edge : graph[v]) {
            int w = edge[1], c = edge[2];
            if(dist[w] > dist[v] + c) {
                dist[w] = dist[v] + c;
                pq.push(edge);
            }
        }
    };
    relax(s);
    while (pq.size()) {
        vector<int> edge = pq.top(); pq.pop();
        if(!marked[edge[1]]) relax(edge[1]);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> m >> n ;
    grid = vector(n, vector(m, '.'));
    graph.assign((n * m) * 4 + 1, {});
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    char c;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> c;
            grid[i][j] = c;
            if(c == '*') continue;
            if(c == 'C') {
                if(x1 == -1) x1 = i, y1 = j;
                else x2 = i, y2 = j;
            }
            // 在base pose上加0,1,2,3，分别代表光线方向为上下左右
            int p1 = (i * m + j) * 4, p2 = -1;
            if(j - 1 >= 0 && grid[i][j - 1] != '*') { // 当前点与左边点的联系
                p2 = (i * m + j - 1) * 4;
                graph[p1].push_back({p1,p2 + 2, 1});
                graph[p1 + 1].push_back({p1 + 1, p2 + 2, 1});
                graph[p1 + 2].push_back({p1 + 2, p2 + 2, 0});
                graph[p2].push_back({p2, p1 + 3, 1});
                graph[p2 + 1].push_back({p2 + 1, p1 + 3, 1});
                graph[p2 + 3].push_back({p2 + 3, p1 + 3, 0});
            }
            if(i - 1 >= 0 && grid[i - 1][j] != '*') { // 当前点与上边点的联系
                p2 = ((i - 1) * m + j) * 4;
                graph[p1 + 2].push_back({p1 + 2, p2, 1});
                graph[p1 + 3].push_back({p1 + 3, p2, 1});
                graph[p1].push_back({p1, p2, 0});
                graph[p2 + 2].push_back({p2 + 2, p1 + 1, 1});
                graph[p2 + 3].push_back({p2 + 3, p1 + 1, 1});
                graph[p2 + 1].push_back({p2 + 1, p1 + 1, 0});
            }
        }
    }
    int pos1 = (x1 * m + y1) * 4, pos2 = (x2 * m + y2) * 4, ans = max_val;
    for(int i = 0; i < 4; i++) {
        dijkstra(pos1 + i);
        for(int j = 0; j < 4; j++)
            ans = min(ans, dist[pos2 + j]);
    }
    cout << ans << endl;
}