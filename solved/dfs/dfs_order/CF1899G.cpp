/**
 * @Time : 2024/9/26-11:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1899G dfs序 线段树 前缀和思想
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5, mod = 998244353;
int T, n, q, p[N], tim, dfn[N], cnt[N], los[N], his[N], xs[N], ans[N], pre[N];
vector<vector<int>> graph;
map<int, vector<int>> lqs, rqs; // 询问中l/r到对应到询问编号的映射

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs];
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        // down(x);
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};


// 计算dfs序 及子树大小
void dfs(int v, int f) {
    dfn[v] = tim++, cnt[v] = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
        cnt[v] += cnt[w];
    }
}
/*
 * 对于询问l r x，求排列p[l, r]上这些结点是否有时间戳在x的子树范围内（dfn[x], dfn[x] + cnt[x] - 1）
 * 可以参考前缀和的思路
 * 计算p[0, l-1]上这些结点时间戳范围在[dfn[x], dfn[x] + cnt[x] - 1]的数量
 * 计算p[0, r]上这些结点时间戳范围在[dfn[x], dfn[x] + cnt[x] - 1]的数量
 * 然后做差即可 范围求和使用线段树
 */
void solve() {
    SegmentTree tree(n + 1); // n个结点 dfs序的时间戳最多到n
    for(int i = 0; i <= n; i++) { // 枚举查询中的位置
        if(i != 0) tree.add(dfn[p[i]], 1); // 相应时间戳上 计数+1
        for(int id : lqs[i + 1]) {
            int x = xs[id], tl = dfn[x], tr = dfn[x] + cnt[x] - 1;
            pre[id] = tree.search(tl, tr);
        }
        for(int id : rqs[i]) {
            int x = xs[id], tl = dfn[x], tr = dfn[x] + cnt[x] - 1;
            int cur = tree.search(tl, tr);
            ans[id] = cur - pre[id];
        }
    }
    for(int i = 1; i <= q; i++)
        cout << (ans[i] > 0 ? "YES" : "NO") << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> q;
        tim = 1, graph.assign(n + 1, {}), lqs = {}, rqs = {};
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        for(int i = 1; i <= n; i++)
            cin >> p[i];
        dfs(1, -1);
        for(int i = 1; i <= q; i++) {
            cin >> los[i] >> his[i] >> xs[i];
            lqs[los[i]].push_back(i), rqs[his[i]].push_back(i);
        }
        solve();
        cout << "\n";
    }
};