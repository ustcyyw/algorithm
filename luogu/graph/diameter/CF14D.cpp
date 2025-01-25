/**
 * @Time : 2025/1/24-9:18 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF14D 1900 图论 树的直径 暴力枚举
 */
 /*
  * 最终答案选中的两条路径 没有公共的点 他们一定在两个子树中
  * 因此枚举第一条路径所在的子树的根结点 就能划分出2个子树
  * 然后计算两个子树的直径
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 205, mod = 998244353;
int T, n, father[N];
set<int> graph[N];

void dfs1(int v, int f) {
    father[v] = f;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v);
    }
}

int dfs2(int v, int f, vector<int>& diameter) {
    int d1 = -1, d2 = -1;
    for(int w : graph[v]) {
        if(w == f) continue;
        int t = dfs2(w, v, diameter);
        diameter[v] = max(diameter[w], diameter[v]);
        if(t > d1) d2 = d1, d1 = t;
        else if(t > d2) d2 = t;
    }
    int t = d2 == -1 ? d1 + 1 : d1 + d2 + 2;
    diameter[v] = max(t, diameter[v]);
    return d1 + 1;
}

void solve() {
    vector<int> diameter(n + 1);
    dfs1(1, -1), dfs2(1, -1, diameter);
    ll ans = 0;
    for(int i = 2; i <= n; i++) {
        graph[father[i]].erase(i);
        vector<int> aux(n + 1);
        dfs2(1, -1, aux);
        ans = max(ans, (ll)aux[1] * diameter[i]);
        graph[father[i]].insert(i);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].insert(w), graph[w].insert(v);
        }
        solve();
    }
};