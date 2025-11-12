/**
 * @Time : 2025/6/3-16:54
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1076E 1900 dfs
 */
 /*
  * reduce[i]: 深度为i的结点需要从 sum - reduce[i]
  * dfs进入的时候 加上这个结点对子树的影响 并且更新reduce
  * dfs退出的时候 将这个结点对子树的影响抹除
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, M = 1e6 + 5, mod = 998244353;
ll T, n, m, ans[N];
vector<int> graph[N];
vector<vector<int>> infos[N];

void dfs(int v, int f, int depth, ll sum, map<int, ll>& reduce) {
    sum -= reduce[depth];
    for(auto& p : infos[v]) {
        sum += p[1];
        reduce[p[0] + depth + 1] += p[1];
    }
    ans[v] = sum;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v, depth + 1, sum, reduce);
    }
    for(auto& p : infos[v])
        reduce[p[0] + depth + 1] -= p[1];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    cin >> m;
    for(int i = 1, v, d, x; i <= m; i++) {
        cin >> v >> d >> x;
        infos[v].push_back({d, x});
    }
    map<int, ll> temp;
    dfs(1, -1, 0, 0ll, temp);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}