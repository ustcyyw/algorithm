/**
 * @Time : 2023/5/11-9:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 101;
// dist[i][j] 表示i到j的最短距离
int n, m, marked[N], dist[N][N], grid[N][N], max_val = 1e9;
long long cnt[N][N];
void dijkstra(int s) {
    fill(marked, marked + n + 1, false);
    dist[s][s] = 0, cnt[s][s] = 1;
    for(int i = 1; i <= n; i++) {
        int v = -1, val = max_val;
        for(int j = 1; j <= n; j++) {
            if(marked[j]) continue;
            val = min(val, dist[s][j]);
            if(val == dist[s][j]) v = j;
        }
        marked[v] = true;
        for(int w = 1; w <= n; w++) {
            if(marked[w]) continue;
            if(dist[s][w] > dist[s][v] + grid[v][w]) {
                cnt[s][w] = cnt[s][v];
                dist[s][w] = dist[s][v] + grid[v][w];
            } else if(dist[s][w] == dist[s][v] + grid[v][w])
                cnt[s][w] += cnt[s][v];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    memset(cnt, 0, sizeof(cnt));
    cin >> n >> m ;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            dist[i][j] = dist[j][i] = max_val;
            grid[i][j] = grid[j][i] = max_val;
        }
        grid[i][i] = 0;
    }
    for(int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c;
        grid[a][b] = grid[b][a] = c;
    }
    for(int i = 1; i <= n; i++)
        dijkstra(i);
    for(int i = 1; i <= n; i++) {
        long double ans = 0;
        for(int v = 1; v <= n; v++) {
            if(v == i) continue;
            for(int w = v + 1; w <= n; w++) {
                if(w == i) continue;
                if(dist[v][w] != max_val && dist[v][i] + dist[i][w] == dist[v][w])
                    ans += cnt[v][i] * cnt[i][w] * 2.0 / cnt[v][w];
            }
        }
        printf("%.3Lf\n", ans);
    }
}