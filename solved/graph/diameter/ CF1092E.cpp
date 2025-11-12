/**
 * @Time : 2024/4/26-10:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1092E 贪心 + 树的直径
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
 *
 * 星型图形成的网络直径最短 那么多个分量连接 选择一个分量为中心 其它分量连接到它
 * 并且连接时使用直径的中点连接
 *
 * 接下来就是确定哪一个分量为中心（可以暴力枚举 n <= 1000）
 * 假设中心点为x，其到直径两端的最大距离为xl
 * 另外两个连接到x的分量的半径中点分别为y z，到相应直径两端的最大距离为yl, zl
 * 那么直径可能的情况
 * 1. 原本三个分量中直径的最大值
 * 2. xl + yl + 1, xl + zl + 1
 * 3. yl + zl + 2
 * 第一种情况并不会使合并后半径增大 不用考虑。下面考虑2和3
 * 如果xl是最大的： 2中是最长的半径 + 别的半径 + 1；而3中是两个较小半径相加后 + 2
 * 如果xl不是最大的： 2中是最长的半径 + xl（相当于其它半径）+ 1； 而3中是最大半径 + 别的半径 + 2
 * 只有xl是最大的情况 才能保证最长的那一条直径最多只会吃到一次连边的贡献
 * 因此中心点应该选最大直径的中点
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005;
int n, m, d[N], a[N], b[N], marked[N];
vector<int> graph[N];
vector<vector<int>> ans;

vector<int> dfs(int v, int f, int root) {
    marked[v] = root;
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
        if(d1 + 1 >= d[root]) d[root] = d1 + 1, a[root] = v, b[root] = n1;
    } else if(d1 + d2 + 2 > d[root])
        d[root] = d1 + d2 + 2, a[root] = n1, b[root] = n2;
    if(d1 == -1) return {0, v};
    return {d1 + 1, n1};
}

int findMid(int node1, int node2, int len) {
    if(node2 == -1) return node1;
    int res = -1;
    function<bool(int, int, int)> dfs2 = [&](int v, int f, int depth) -> bool {
        if(v == node2) return true;
        int flag = false;
        for(int w : graph[v]) {
            if(w == f) continue;
            flag |= dfs2(w, v, depth + 1);
            if(flag) break;
        }
        if(flag && depth == len / 2) res = v;
        return flag;
    };
    dfs2(node1, -1, 0);
    return res;
}

void solve() {
    vector<int> mid; // 存放各个中点
    int id = -1, v = -1; // 标记成为中心的分量
    for(int i = 1; i <= n; i++) {
        if(marked[i] > 0) continue;
        dfs(i, -1, i);
        mid.push_back(findMid(a[i], b[i], d[i]));
        if(id == -1 || d[id] < d[i]) {
            id = i; // 半径最大的分量成为中心
            v = mid.back();
        }
    }
    for(int w : mid) {
        if(w != v) {
            ans.push_back({v, w});
            graph[v].push_back(w), graph[w].push_back(v);
        }
    }
    dfs(v, -1, v);
    cout << d[v] << "\n";
    for(auto& edge : ans)
        cout << edge[0] << " " << edge[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
};