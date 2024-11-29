/**
 * @Time : 2024/6/18-11:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1294F 利用树直径的性质
 */
/*
 * 选取三个点 他们互相往对方走 会走到一个交点
 * 枚举每个点作为交点 维护这个点出发的最长路径 次长路径和第三长路径
 * 换根dp
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, ans = 0, a, b, c;
vector<int> graph[N];
vector<vector<int>> edge1, edge2, edge3;

int diff() {
    for(int i = 1; i <= 3; i++)
        if(i != a && i != b) return i;
    return -1;
}

void cal_len(int v) {
    int len = edge1[v][0] + edge2[v][0] + edge3[v][0];
    if(len <= ans) return;
    ans = len;
    a = edge1[v][2];
    b = edge2[v][2] == 0 ? v : edge2[v][2];
    c = edge3[v][2] == 0 ? diff() : edge3[v][2];
}

void update(int v, vector<int>& t, int w) {
    if(edge1[v][0] <= t[0] + 1) {
        edge3[v] = edge2[v];
        edge2[v] = edge1[v];
        edge1[v] = {t[0] + 1, w, t[2]};
    } else if(edge2[v][0] <= t[0] + 1) {
        edge3[v] = edge2[v];
        edge2[v] = {t[0] + 1, w, t[2]};
    } else if(edge3[v][0] < t[0] + 1)
        edge3[v] = {t[0] + 1, w, t[2]};
}

void dfs1(int v, int f) {
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v);
        update(v, edge1[w], w);
    }
    if(edge1[v][0] == 0) edge1[v] = {0, v, v};
}

void dfs2(int v, int f) {
    if(f == -1) {
        if(edge2[v][2] == 0) edge2[v] = {0, 1, 1}; // 根结点本身也是个叶子结点时 需要补一条简单路径
        cal_len(v);
    } else {
        vector<int> t = edge1[f][1] == v ? edge2[f] : edge1[f];
        update(v, t, f);
        cal_len(v);
    }
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs2(w, v);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    edge1 = vector(n + 1, vector(3, 0));
    edge2 = vector(n + 1, vector(3, 0));
    edge3 = vector(n + 1, vector(3, 0));
    dfs1(1, -1), dfs2(1, -1);
    cout << ans << "\n";
    cout << a << " " << b << " " << c;
};