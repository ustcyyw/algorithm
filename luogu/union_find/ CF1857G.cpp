/**
 * @Time : 2024/9/12-9:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1857G 并查集 图论 最小生成树
 */
 /*
  * 要保证最小生成树唯一且就是题目给的树
  * 在不出现重边的情况下 任意两个点相连 会出现一个环 记环中其它边权的最大值是mw
  * 如果这条新的边权 < mw 那么这个图的最小生成树就不是题目所给的树
  * 如果这条新的边权 = mw 那么这个图的最小生成树就不是唯一的
  * 因此连出来的边权 > mw
  * 可选的范围就是 [mw + 1，s]
  * 当然这两个点之间也可以没有边 因此这两个点之间边的可能情况是 s - (mw + 1) + 1 + 1 = s - mw + 1
  * 任意两个点对之间是独立的 因此使用乘法原理
  *
  * 接下来要解决的问题就是确定点对之间选择的可能性
  * 枚举点对 时间复杂度不够
  * 既然是和环中最大边权有关 借鉴离线算法思路 先将边权排序
  * 从小到达枚举边权 不断将不同点连通
  * 假设当前枚举的边权为w，两个连通分量p和q要连通了
  * 那么这两个分量之间的点连接后形成的环 其它边权最大就是w
  * 这些点对可取的权种都是[w+1，s]或者不连，共有sz[q] * sz[p] - 1个点对（注意不能有重边）
  * 这些点对的乘 就可以使用快速幂
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, s;
vector<int> id, sz;
vector<vector<int>> edges;

ll qp(ll a, ll b) {
    ll res = 1;
    while (b != 0){
        if((b & 1) == 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int find(int p) {
    return id[p] = id[p] == p ? p : find(id[p]);
}

ll connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return 0;
    ll cnt = (ll)sz[q] * sz[p] - 1;
    sz[q] += sz[p], id[p] = q;
    return cnt;
}

void solve() {
    sort(edges.begin(), edges.end());
    ll ans = 1;
    for(auto& edge : edges) {
        int w = edge[0], u = edge[1], v = edge[2];
        ll cnt = connect(u, v);
        ans = ans * qp((s - w + 1), cnt) % mod;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> s;
        edges = {};
        id.assign(n + 1, 0), sz.assign(n + 1, 1);
        for(int i = 1; i <= n; i++)
            id[i] = i;
        for(int i = 1, u, v, w; i < n; i++) {
            cin >> u >> v >> w;
            edges.push_back({w, u, v});
        }
        solve();
    }
};