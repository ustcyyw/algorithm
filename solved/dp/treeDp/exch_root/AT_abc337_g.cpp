/**
 * @Time : 2024/3/27-10:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 换根dp 发现转移时候的一个重点 就是看子树中有多少个比自己小的结点
  * f -> v转移时 来自f另外一侧比v小的结点，都能和v构成满足的数对
  * 但是原本f向v这一侧的比f小的结点，将无法与f再构成满足的数对
  * low[x]:x的子树中比x小的结点数目
  * flow[x]:x的子树中比其父结点小的结点数目
  * 那么转移 ans[v] = ans[f] + v - 1 - low[v] - flow[v]
  * v - 1 - low[v]表示来自f另外一侧比v小的结点
  *
  * 要计算low[x]和flow[x]可以参考 P3605题
  * 使用线段树来计数
  */
#define ls x << 1
#define rs (x << 1) | 1
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, low[N], flow[N], val[4 * N];
ll ans[N], aux[N];
vector<int> graph[N];

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
    int mid = (l + r) >> 1, res = 0;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) res += search(rs, mid + 1, r, a, b);
    return res;
}

void dfs1(int v, int f) {
    add(1, 1, n, v, 1);
    int cnt1 = search(1, 1, n, 1, v);
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v);
        aux[v] += aux[w];
    }
    int cnt2 = search(1, 1, n, 1, v);
    low[v] = cnt2 - cnt1; // 记录v子树中比v小的结点数目
    aux[v] += low[v];
}

void dfs2(int v, int f) {
    int cnt1 = 0;
    if(f != -1) cnt1 = search(1, 1, n, 1, f);
    add(1, 1, n, v, 1);
    for(int w : graph[v])
        if(w != f) dfs2(w, v);
    if(f != -1) {
        int cnt2 = search(1, 1, n, 1, f);
        flow[v] = cnt2 - cnt1;
    }
}

void dfs3(int v, int f) {
    if(f != -1)
        ans[v] = ans[f] + v - 1 - low[v] - flow[v];
    for(int w : graph[v])
        if(w != f) dfs3(w, v);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    memset(graph, {}, sizeof(graph));
    memset(val, 0, sizeof(val));
    for(int i = 0, v, w; i < n - 1; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs1(1, -1);
    ans[1] = aux[1];
    memset(val, 0, sizeof(val));
    dfs2(1, -1);
    dfs3(1, -1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
};