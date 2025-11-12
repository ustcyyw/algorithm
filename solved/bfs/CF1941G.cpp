/**
 * @Time : 2024/4/2-8:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 颜色和站点构成的二分图
  * 站点只能走到颜色点 颜色点只能走到站点
  * 同一条地铁上的站点 通过连接到同一个颜色而连通 因此两步才能从走到同一个颜色的站点
  * 而要到另外一个颜色的地铁线 就得到同一个颜色的其它站点换乘
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 50, B = 2e5 + 5;
int T, n, m, b, e, marked[N];
unordered_map<int, unordered_set<int>> graph;

void add(int v1, int v2) {
    graph[v1].insert(v2), graph[v2].insert(v1);
}

int solve() {
    int step = 1;
    queue<int> queue;
    queue.push(b), marked[b] = 1;
    while(true) {
        int sz = queue.size();
        for(int i = 0; i < sz; i++) {
            int v = queue.front();
            for(int w : graph[v]) {
                if(marked[w]) continue;
                marked[w] = 1, queue.push(w);
                if(marked[e]) return step / 2;
            }
            queue.pop();
        }
        step++;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        graph.clear();
        memset(marked, 0, sizeof(marked));
        cin >> n >> m;
        for(int i = 0, v, w, c; i < m; i++) {
            cin >> v >> w >> c;
            int idc = c + B;
            add(v, idc), add(w, idc);
        }
        cin >> b >> e;
        cout << solve() << "\n";
    }
};