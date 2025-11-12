/**
 * @Time : 2024/4/26-11:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF455C 树的直径 + 并查集
 */
/*
 * 树上任意一点到其它点的最长路径 其终点一定是直径的两个端点之一
 * 假设现在连接两个分量a和b：a中一点ai 连b中一点bi 形成新的树 直径只会有三种可能
 * 1.原本a的直径ad
 * 2.原本b的直径bd
 * 3.ai到a中最远点 ai - bi bi到b中最远点构成的路径
 * 三者取最大 1和2是确定的，唯一的变数就在3
 * 因此每次连通两个分量都应该让3最小
 * 在ai固定的情况下 如果bi不在bd的中心点b_mid 那么bi到bd两端的最远距离 > b_mid到bd两端的最远距离
 * 所以应该取bi为bd的中心点 同理ai也是
 * 也就是说只考虑两个分量的连接 一定是将两个分量中直径的中点进行连接
 * 两中点连接 计算3的可能长度 (ad + 1)/ 2 + (bd + 1) / 2 + 1。 注意向上取整
 *
 * 两个分量合并 并不需要关注直径中点具体是哪点 维护好合并后的直径长度即可
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int n, m, k, d[N], id[N];
vector<int> graph[N];

vector<int> dfs(int v, int f, int root) {
    id[v] = root;
    int d1 = -1, n1 = -1, d2 = -1, n2 = -1;
    for(int w : graph[v]) {
        if(w == f) continue;
        vector<int> temp = dfs(w, v, root);
        int d3 = temp[0], n3 = temp[1];
        if(d3 >= d1) {
            d2 = d1, d1 = d3;
            n2 = n1, n1 = n3;
        } else if(d3 > d2)
            d2 = d3, n2 = n3;
    }
    if(d2 == -1) {
        if(d1 + 1 >= d[root]) d[root] = d1 + 1;
    } else if(d1 + d2 + 2 > d[root])
        d[root] = d1 + d2 + 2;
    if(d1 == -1) return {0, v};
    return {d1 + 1, n1};
}

void init() {
    for(int i = 1; i <= n; i++)
        id[i] = i;
    for(int i = 1; i <= n; i++) {
        if(id[i] != i) continue;
        dfs(i, -1, i);
    }
}

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

void merge(int x, int y) {
    int p = find(x), q = find(y);
    if(p == q) return;
    int d1 = d[p], d2 = d[q];
    id[p] = q;
    d[q] = max({d1, d2, (d1 + 1) / 2 + (d2 + 1) / 2 + 1});
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    init();
    for(int i = 1, t, x, y; i <= k; i++) {
        cin >> t >> x;
        if(t == 1) {
            cout << d[find(x)] << "\n";
        } else {
            cin >> y;
            merge(x, y);
        }
    }
};