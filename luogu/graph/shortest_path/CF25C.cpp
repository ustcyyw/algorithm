/**
 * @Time : 2025/1/28-9:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF25C 1900 图论 最短路 floyd 动态加边
 */
 /*
  * 已经给定了图的dis矩阵
  * 并且每次添加一个边 让求最短路径相关的东西 显然是floyd算法
  * 只需要注意原本的floyd算法是针对有向图的
  * 本题是无向图 那么只需要将添加的边 当作2条有向边添加即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 305, mod = 998244353;
int T, n, k, dis[N][N];
ll sum = 0;

void add(int v, int w, int c) {
    if(c >= dis[v][w]) return;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int p = dis[i][j];
            dis[i][j] = min(dis[i][j], dis[i][v] + c + dis[w][j]);
            sum -= p - dis[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                cin >> dis[i][j];
                sum += dis[i][j];
            }
        }
        cin >> k;
        for(int i = 1, v, w, c; i <= k; i++) {
            cin >> v >> w >> c;
            add(v, w, c), add(w, v, c);
            cout << sum / 2 << " ";
        }
    }
};