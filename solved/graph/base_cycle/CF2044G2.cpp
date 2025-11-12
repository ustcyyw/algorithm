/**
 * @Time : 2024/12/16-3:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2044G2 图论 基环树 拓扑排序
 */
 /*
  * 找结点最多的树枝
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, r[N], degree[N], cycle[N], cnt[N];

void topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(), w = r[v]; queue.pop();
        cycle[v] = 0, cnt[w] += cnt[v];
        if(--degree[w] == 0) queue.push(w);
    }
}

void solve() {
    topol_bfs();
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        int w = r[i];
        if(cycle[w] && !cycle[i]) ans = max(ans, cnt[i] + 1);
    }
    cout << ans + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        fill(degree, degree + n + 1, 0);
        fill(cycle, cycle + n + 1, 1);
        fill(cnt, cnt + n + 1, 1);
        for(int i = 1; i <= n; i++) {
            cin >> r[i];
            degree[r[i]]++;
        }
        solve();
    }
};