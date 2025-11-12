/**
 * @Time : 2025/4/28-5:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1009F 2300 启发式合并 树上启发式合并
 */
 /*
  * 树上启发式合并 可以解决离线问题
  * 一般将重儿子（就是结点数目最多的子树）当做基准，将其它儿子的结算结果合并进重儿子
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 998244353;
int T, n, ans[N], ansC[N], depth[N], cnt[N], son[N] = {0};
vector<int> graph[N];

void dfs1(int v, int f, int d) {
    depth[v] = d, cnt[v] = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v, d + 1);
        cnt[v] += cnt[w];
        if(cnt[son[v]] < cnt[w]) son[v] = w;
    }
}

map<int, int> dfs2(int v, int f) {
    ans[v] = depth[v], ansC[v] = 1;
    if(son[v] == 0) return {{depth[v], 1}};
    int s = son[v];
    map<int, int> base = dfs2(s, v);
    base[depth[v]] = 1;
    if(ansC[s] > ansC[v])
        ansC[v] = ansC[s], ans[v] = ans[s];
    for(int w : graph[v]) {
        if(w == f || w == s) continue;
        map<int, int> temp = dfs2(w, v);
        for(auto& [d, c] : temp) {
            base[d] += c;
            if(base[d] > ansC[v] || (base[d] == ansC[v] && ans[v] > d)) {
                ans[v] = d;
                ansC[v] = base[d];
            }
        }
    }
    return base;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        graph[a].push_back(b), graph[b].push_back(a);
    }
    dfs1(1, -1, 0);
    dfs2(1, -1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] - depth[i] << "\n";
}