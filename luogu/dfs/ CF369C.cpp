/**
 * @Time : 2023/12/7-8:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const long long T = 1e6, N = 2e5 + 5;
int n, marked[N], nodes[N], cnt;
unordered_set<long long> st;
vector<vector<int>> graph;

long long get_key(int a, int b) {
    return T * max(a, b) + min(a, b);
}

bool dfs(int v, int f) {
    marked[v] = 1;
    long long key = f == -1 ? -1 : get_key(v, f);
    bool flag = false;
    for(int w : graph[v]) {
        if(marked[w]) continue;
        flag |= dfs(w, v);
    }
    if(!flag && st.count(key))
        flag = true, nodes[v] = 1, cnt++;
    return flag;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(marked, 0, sizeof(marked)), memset(nodes, 0, sizeof(nodes));
    cin >> n;
    graph.assign(n + 1, {});
    for(int i = 0, a, b, w; i < n - 1; i++) {
        cin >> a >> b >> w;
        graph[a].push_back(b), graph[b].push_back(a);
        if(w == 2) st.insert(get_key(a, b));
    }
    cnt = 0;
    dfs(1, -1);
    cout << cnt << endl;
    for(int i = 1; i <= n; i++)
        if(nodes[i]) cout << i << " ";
}