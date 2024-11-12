/**
 * @Time : 2024/11/11-11:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1931F 图论 拓扑排序
 */
 /*
  * 明显的前后顺序 是否出现矛盾就是在拓扑序中是否有环
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, degree[N];
vector<vector<int>>graph;

bool check() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    int cnt = 0;
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        cnt++;
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
    return cnt == n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        fill(degree, degree + n + 1, 0);
        graph.assign(n + 1, {});
        for(int i = 1, t; i <= k; i++) {
            cin >> t;
            for(int j = 2, v = -1, w; j <= n; j++) {
                cin >> w;
                if(v != -1) graph[v].push_back(w), degree[w]++;
                v = w;
            }
        }
        cout << (check() ? "YES" : "NO") << "\n";
    }
};