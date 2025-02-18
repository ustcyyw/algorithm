/**
 * @Time : 2025/2/17-5:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1286B 1800 构造 dfs
 */
 /*
  * c[i]: 表示i在子树中排名第 c[i] + 1
  * 在dfs的过程中 假设所有子结点都已经排好名了 那么当前根结点 就插入到第c[i]个位置的后面即可
  * dfs完成后 按顺序赋值即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e3 + 5, mod = 1e9 + 7;
ll T, n, c[N], root, ans[N], cnt[N];
vector<int> graph[N], nodes[N];

void dfs(int v) {
    cnt[v] = 1;
    if(graph[v].empty())
        nodes[v].push_back(v);
    for(int w : graph[v]) {
        dfs(w);
        cnt[v] += cnt[w];
        for(int node : nodes[w]) {
            if(nodes[v].size() == c[v]) nodes[v].push_back(v);
            nodes[v].push_back(node);
        }
    }
    if(nodes[v].size() == c[v]) nodes[v].push_back(v);
}

bool solve() {
    dfs(root);
    for(int i = 1; i <= n; i++) {
        if(cnt[i] - 1 < c[i])
            return false;
    }
    for(int i = 0; i < n; i++)
        ans[nodes[root][i]] = i + 1;
    return true;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1, f; i <= n; i++) {
            cin >> f >> c[i];
            if(f != 0) graph[f].push_back(i);
            else root = i;
        }
        if(!solve()) cout << "NO";
        else {
            cout << "YES\n";
            for(int i = 1; i <= n; i++)
                cout << ans[i] << " ";
        }
    }
};