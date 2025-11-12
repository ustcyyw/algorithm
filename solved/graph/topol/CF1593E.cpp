/**
 * @Time : 2024/3/19-11:27 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 5;
int T, n, k, degree[N], marked[N];
vector<vector<int>> graph;

int solve() {
    if(k * 2 >= n) return 0;
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 1) queue.push(i), marked[i] = 1;
    int cnt = 0;
    while (!queue.empty() && k--) {
        int sz = queue.size();
        for(int i = 0; i < sz; i++) {
            int v = queue.front(); queue.pop();
            for(int w : graph[v])
                if(--degree[w] <= 1 && !marked[w])
                    queue.push(w), marked[w] = 1;
        }
        cnt += sz;
    }
    return n - cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        memset(degree, 0, sizeof(degree)), memset(marked, 0, sizeof(marked));
        graph.assign(n + 1, vector(0, 0));
        for(int i = 0, v, w; i < n - 1; i++) {
            cin >> v >> w;
            degree[v]++, degree[w]++;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cout << solve() << "\n";
    }
};