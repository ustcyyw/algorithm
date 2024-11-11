/**
 * @Time : 2024/6/18-8:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1294F 换根dp
 */
/*
 * 选取三个点 他们互相往对方走 会走到一个交点
 * 枚举每个点作为交点 维护这个点出发的最长路径 次长路径和第三长路径
 * 换根dp
 */

/*
 * 从换根dp的思路可知 就是要找某个点前三长的简单路径
 * 本题也可以利用树的直径的性质：
 * 回顾 树上任意一点到其它点的最大距离 一定是到直径的某个端点之一
 * 假设直径的端点为 x,y。枚举的交点为v
 *
 * 1.v在直径上 并且假设v的最长简单路径是 v-x 场地为dis(v,x)
 * 假设v的子树 除了到x和y外的最长简单路径是 v-a
 * dis(v,x) >= dis(v,a), 由直径的性质可得
 * dis(v,y) >= dis(v,a), 由反证法，如果是dis(v,y) < dis(v,a)
 * 那么 dis(v,y) + dis(v,x) < dis(v,a) + dis(v,x), a-v-x才是直径 与原本的假设矛盾
 * 于是可知第一 第二长的路径就是v到直径的两个端点
 * 第三长的路径则是从直径上的v点再找一条最长路径
 *
 * 2.v不在直径上 并且假设v到直径的简单路径与直径交点为u
 * 在1中已经说明了
 * dis(u,x) >= dis(u,a) = dis(u,v) + dis(v,a)
 * dis(u,y) >= dis(u,a) = dis(u,v) + dis(v,a)
 * 因此
 * dis(u,x) > dis(v,a)
 * dis(u,y) > dis(v,a)
 * 左边再加上 dis(u,v)
 * dis(u,x) + dis(u,v) = dis(v,x) > dis(v,a)
 * dis(u,y) + dis(u,v) = dis(v,y) > dis(v,a)
 * 因此依旧的出结论 第一 第二长的路径就是v到直径的两个端点 第三长的路径则是从直径上的v点再找一条最长路径
 *
 * 于是就证明了 不管选哪个点为交叉点  第一 第二长的路径就是交叉点到直径的两个端点
 * 那么就可以直接将直径找到 再找到直径上一个点到其它叶子结点的最长路径
 * 这样就找齐了答案中的三条路径
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