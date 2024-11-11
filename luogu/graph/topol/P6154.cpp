/**
 * @Time : 2023/5/17-6:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * cnt[i]以i为结尾的路径数目
 * cnt[i] = sigma(cnt[j]) + 1，加和是指所有 j->i 的边（因为有重边），1就是i结点本身。
 * len[i]以i为结尾的路径长度之和
 * len[i] = sigma(cnt[j] + len[j])，加和是指所有 j->i 的边（因为有重边）
 * 第一项，是因为每一条以j为结尾的路径，通过 j->i 到i，长度都增加1
 * 第二项，是这些路径原本的长度len[j]
 * 两项加在一起才是原本以j为结尾且通过j->i到达i的路径总长
 *
 * 于是发现要先知道前置结点的情况，才知道当前结点的情况，按拓扑的顺序进行计算（刷表）
 */
#include<bits/stdc++.h>

#define ll long long
using namespace std;
const int N = 1e5 + 5, mod = 998244353;
int n, m, degree[N];
ll cnt[N], len[N];
vector<vector<int>> graph;

void topol_sort() {
    queue<int> queue;
    for (int i = 1; i <= n; i++)
        if (degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front();
        queue.pop();
        for (int w: graph[v]) {
            cnt[w] = (cnt[w] + cnt[v]) % mod;
            len[w] = (len[w] + cnt[v] + len[v]) % mod;
            if (--degree[w] == 0) queue.push(w);
        }
    }
}

long long Power(long long x, long long y, long long mod) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); // 加速cin, cout
    cin >> n >> m;
    fill(cnt, cnt + n + 1, 1);
    fill(len, len + n + 1, 0);
    graph.assign(n + 1, {});
    for (int i = 0, v, w; i < m; i++) {
        cin >> v >> w;
        graph[w].push_back(v), degree[v]++;
    }
    topol_sort();
    long long total = 0, total_len = 0;
    for (int i = 1; i <= n; i++)
        total = (total + cnt[i]) % mod, total_len = (total_len + len[i]) % mod;
    cout << (total_len * Power(total, mod - 2, mod)) % mod << endl;
}