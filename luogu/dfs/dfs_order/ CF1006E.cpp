/**
 * @Time : 2024/4/9-9:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
int n, m, tim, order[N], ro[N], cnt[N];
vector<int> graph[N];

void dfs(int v) {
    ++tim;
    order[v] = tim, ro[tim] = v;
    cnt[v] = 1;
    for(int w : graph[v]) {
        dfs(w);
        cnt[v] += cnt[w];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 2, v; i <= n; i++) {
        cin >> v;
        graph[v].push_back(i);
    }
    tim = 0;
    dfs(1);
    for(int i = 1, u, k; i <= m; i++) {
        cin >> u >> k;
        if(k > cnt[u]) cout << -1 << "\n";
        else cout << ro[order[u] + k - 1] << "\n";
    }
};