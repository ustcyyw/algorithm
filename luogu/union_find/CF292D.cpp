/**
 * @Time : 2024/1/25-3:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 并查集合并
 */

/*
 * 考虑到n比较小 并且问题是无向图中的连通分量数
 * 可以使用并查集来维护 因为要删除[l,r]中的边 将边的集合分成前后两部分
 * 可以预处理边的前后缀对应的连通情况
 * 已知[1,i-1]上连通状态（也就是一个并查集表示的情况）
 * 进行深复制后 再将第i条边的两点union就得到[1,i]上连通状态
 *
 * 删除[l,r]中的边，[1, l-1]和[r+1, n]上的边依旧有效
 * 前缀 后缀相应的并查集copy出来后需要进行合并 因为其中任何一个并查集 都只处理了一部分的边（连通操作）。
 * 如果不关注过程 仅关注最终连通状态（共有多少个连通分量，哪些结点在同一个连通分量）
 * 那么处理连接操作的顺序可以任意调换
 * 因此合并后的并查集就是从头开始处理剩余边的结果
 *
 * 合并并查集的操作：
 * 对于结点i，在前缀中 所属连通分量为p， 在后缀中 所属的连通分量为q
 * 如果p != q 说明这两个连通分量通过i连在一起 要进行union操作，操作的结果仅保留在其中一个并查集即可
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 505, M = 1e4 + 5;
int n, m, k, l, r, edges[M][2];
pair<int, vector<int>> pre[M], suf[M];

int find(pair<int, vector<int>>& uf, int p) {
    if(uf.second[p] == p) return p;
    return uf.second[p] = find(uf, uf.second[p]);
}

void connect(pair<int, vector<int>>& uf, int p, int q) {
    p = find(uf, p), q = find(uf, q);
    if(p == q) return ;
    uf.first--;
    uf.second[p] = q;
}

void init() {
    vector<int> id(n + 1, 0);
    for(int i = 1; i <= n; i++)
        id[i] = i;
    pre[0] = {n, id}, suf[m + 1] = {n, id};
    for(int i = 1; i <= m; i++) {
        pre[i] = pre[i - 1]; // 在cpp中 这就是深复制
        connect(pre[i], edges[i][0], edges[i][1]);
    }
    for(int i = m; i >= 1; i--) {
        suf[i] = suf[i + 1];
        connect(suf[i], edges[i][0], edges[i][1]);
    }
}

int solve() {
    if(l == 1 && r == m) return n;
    if(l == 1) return suf[r + 1].first;
    if(r == m) return pre[l - 1].first;
    // 将前缀 后缀并查集合并。将同一个结点归属的不同编号的分量连通
    pair<int, vector<int>> left = pre[l - 1], right = suf[r + 1];
    for(int i = 1; i <= n; i++) {
        int p = find(left, i), q = find(right, i);
        if(p != q) connect(left, p, q);
    }
    return left.first;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> edges[i][0] >> edges[i][1];
    init();
    cin >> k;
    while(k-- > 0) {
        cin >> l >> r;
        cout << solve() << endl;
    }
}