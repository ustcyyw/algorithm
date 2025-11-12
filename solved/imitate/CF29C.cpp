/**
 * @Time : 2025/1/31-4:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF29C 模拟 dfs
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 300 + 5, M = 2 * N;
int n;
map<int, vector<int>> graph;
map<int, int> degree;

void dfs(int v, int f) {
    cout << v << " ";
    for(int w : graph[v]) {
        if(w != f) dfs(w, v);
    }
}

void solve() {
    int s;
    for(auto& [node, d] : degree) {
        if(d == 1) {
            s = node;
            break;
        }
    }
    dfs(s, -1);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1, v, w; i <= n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
        degree[v]++, degree[w]++;
    }
    solve();
};