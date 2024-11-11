/**
 * @Time : 2024/1/13-1:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 有逆元情况下取mod出现0的情况 可以特殊处理
 */

/*
 * 在固定根的情况下 用f[i]表示 i及其子结点的满足条件的方案数
 * f[v] *= (f[w] + 1)
 * 这里的+1，是指将v-w这条边标记的这种新方案。不同子结点下的标记方案相互独立 因此使用乘法原理
 * 对于根结点来说 ans[v] = f[v]
 *
 * 由于数据规模3e5 容易想到需要使用换根dp
 * 从v转移到子结点w的时候 ans[v] = mul{f[other]} * (f[w] + 1)
 * 那么把w当根结点时，v是w的一个儿子
 * 对其的贡献就是 ans[v] / (f[w] + 1) + 1。这里+1的来源也是w-v这条边
 * 而其它子结点对w的贡献 就是f[w]
 * 因此 ans[w] = f[w] * (ans[v] / (f[w] + 1) + 1)
 *
 * 但是取mod会出现0的情况 要特殊处理
 * 因此用一个二元结构来解决
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5, mod = 1e9 + 7;
ll n;
vector<vector<int>> graph;

struct kx {
public:ll k, x;
};
kx f[N], ans[N];

ll qp(ll a, ll b) {
    ll res = 1;
    while (b != 0){
        if((b & 1) == 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

kx add1(kx p) {
    if (p.k > 0) return kx{0, 1};
    if (p.x == mod - 1) return kx{1, 1};
    return kx{0, p.x + 1};
}

kx mul(kx p, kx q) {
    return kx{p.k + q.k, p.x * q.x % mod};
}

kx div(kx p, kx q) {
    return kx{p.k - q.k, p.x * qp(q.x, mod - 2) % mod};
}

void dfs1(int v, int fa) {
    f[v].x = 1, f[v].k = 0;
    for(int w : graph[v]) {
        if(w == fa) continue;
        dfs1(w, v);
        f[v] = mul(f[v], add1(f[w]));
    }
}

void dfs2(int v, int fa) {
    if(fa != -1) {
        kx p = div(ans[fa], add1(f[v]));
        ans[v] = mul(f[v], add1(p));
    }
    for(int w : graph[v])
        if(w != fa) dfs2(w, v);
}

void solve() {
    dfs1(1, -1);
    ans[1] = f[1];
    dfs2(1, -1);
    for(int i = 1; i <= n; i++)
        cout << (ans[i].k > 0 ? 0 : ans[i].x) << " ";
}

int main(){
    cin >> n;
    graph.assign(n + 1, {});
    for(int i = 2, p; i <= n; i++) {
        cin >> p;
        graph[i].push_back(p), graph[p].push_back(i);
    }
    solve();
}