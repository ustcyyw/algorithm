/**
 * @Time : 2023/5/11-10:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 行走长度为 2 ^ k 次，2的幂次。并且路径长度很大 可以考虑倍增的思路
 * 倍增都有一个维度k，表示2^k
 * 本题中 具体就是两个点之间是否存在长度为2^k的路径，如果存在，只需要一秒就能到达
 * 初始时刻，每个条单向都意味着 存在 v到w的长度为 2 ^ 0 的路径
 * 用 G[i][j][k] 标识是否存在 i -> j 且长度为2 ^ k的路径
 * 如果存在dist[i][j] = 1 表示i -> j 一秒可达
 *
 * 如果存在v使得 G[i][v][k - 1] = G[v][j][k - 1] = true，则 G[i][j][k] = true
 * 从i到v有长度为2 ^ (k - 1)的路径,从v到j也有2 ^ (k - 1)的路径，那么从i->v->j到这条路径长为2 ^ k
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 55, K = 65;
int n, m, dist[N][N], G[N][N][K];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    memset(dist, 10, sizeof(dist));
    memset(G, false, sizeof(G));
    cin >> n >> m;
    for(int i = 0, v, w; i < m; i++) {
        cin >> v >> w;
        dist[v][w] = 1, G[v][w][0] = true;
    }
    for(int k = 1; k <= 64; k++) { // 要求2^k长度的路径情况，要知道2 ^ (k-1)
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                for(int v = 1; v <= n; v++)
                    if(G[i][v][k - 1] && G[v][j][k - 1])
                        dist[i][j] = 1, G[i][j][k] = true;
            }
        }
    }
    // 已经将所有一秒可达的相邻结点找到了，接下来就是看起点到终点的最短路
    // 已经有邻接矩阵了 floyd算法比较方便
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
    cout << dist[1][n] << endl;
}