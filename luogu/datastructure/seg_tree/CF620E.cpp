/**
 * @Time : 2024/3/28-2:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * dfs序 将树变为区间
  * order[v]: 结点v的dfs序；ro[time] 序time对应的结点的编号
  * 于是针对子树的操作就变为针对区间的操作 使用线段树
  * 因为总归只有60个颜色 状态压缩 可以用long long变量存放颜色信息
  */
#define ls x << 1
#define rs (x << 1) | 1
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 5, mod = 1e9 + 7;
int n, m, c[N], cnt[N], order[N], ro[N], tim, tag[4 * N];
ll val[4 * N];
vector<int> graph[N];

void update(int x) {
    val[x] = 0;
    val[x] |= val[ls], val[x] |= val[rs];
}

void down(int x) {
    if(tag[x] == 0) return;
    tag[ls] = tag[rs] = tag[x];
    val[ls] = 1ll << tag[x], val[rs] = 1ll << tag[x];
    tag[x] = 0;
}

void build(int x, int l, int r) {
    if(l == r) {
        val[x] = 1ll << c[ro[l]]; // 注意这里要先将序转换为结点编号才知道颜色
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    update(x);
}

void change(int x, int l, int r, int a, int b, int v) {
    if(a <= l && r <= b) {
        val[x] = 1ll << v, tag[x] = v;
        return ;
    }
    down(x);
    int mid = (l + r) >> 1;
    if(a <= mid) change(ls, l, mid, a, b, v);
    if(b > mid) change(rs, mid + 1, r, a, b, v);
    update(x);
}

ll search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return val[x];
    int mid = (l + r) >> 1;
    down(x);
    ll res = 0;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) res |= search(rs, mid + 1, r, a, b);
    return res;
}

void dfs(int v, int f) {
    order[v] = ++tim;
    ro[tim] = v;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
        cnt[v] += cnt[w];
    }
    cnt[v]++;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    memset(graph, {}, sizeof(graph));
    memset(tag, 0, sizeof(tag));
    for(int i = 1; i <= n; i++)
        cin >> c[i];
    for(int i = 0, v, w; i < n - 1; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    tim = 0;
    dfs(1, -1);
    build(1, 1, n);
    for(int i = 1, t, u, color; i <= m; i++) {
        cin >> t;
        if(t == 1) {
            cin >> u >> color;
            change(1, 1, n, order[u], order[u] + cnt[u] - 1, color);
        } else {
            cin >> u;
            ll temp = search(1, 1, n, order[u], order[u] + cnt[u] - 1);
            cout << __builtin_popcountll(temp) << "\n";
        }
    }
};