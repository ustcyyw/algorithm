/**
 * @Time : 2024/11/18-11:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1141G 贪心 构造 1900
 */
/*
 * 当k=0时 就是不允许有坏城市 那么边最多的城市 每条边都得不同颜色
 * 其余城市边更少 用这么多颜色能保证不成为坏城市
 * 另外 结合直觉度数越高的城市 将其设置为坏城市更能节约颜色
 *
 * 下面来证明这个结论
 * 一般地 假设k个坏城市的度数分别为 d[i1],d[i2],...d[ik]
 * 其它城市里，城市j度数最大为d[j] > d[i1]（或者其它，比如d[i2]）
 * 那么需要使用的颜色为d[j]种来保证该城市不坏 其余城市因为度数更小 一定能用最多d[j]颜色保证不坏
 * 但是将j城市设置为坏城市，而将i1城市设置为好城市，那么最多还是d[j]种颜色能满足要求
 * 如果交换后，好城市种度数最大的 < d[j]， 那么用少于d[j]种颜色就能满足
 * 因此这样交换至少不坏， 可能更好。于是得出结论 应该将度数最大的k个城市设置为坏城市
 * 剩下的城市中，度数最大的那个就确定了需要使用的颜色
 *
 * 涂色方案：随便某个城市作为起点 初始颜色为1
 * 如果某个城市是坏城市 就将颜色全部设置为1，跳过与父亲节点那条边即可
 * 否则 从颜色1开始依次为每条边涂色 遇到和父亲节点的边不涂色 、
 * 并且要跳过与父亲节点那条边相同的颜色color
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k, ans[N], degree[N], max_c;
vector<vector<vector<int>>> graph;

void dfs(int v, int f, int fc) {
    int cc = 0;
    for(auto& edge : graph[v]) {
        int w = edge[0], idx = edge[1];
        if(w == f) continue;
        if(degree[v] <= max_c) { // 对于好城市 每条边的颜色要不一致
            cc++;
            if(cc == fc) cc++; // 跳过与父亲节点那条边相同的颜色
        } else cc = 1; // 坏城市 颜色固定为1
        ans[idx] = cc, dfs(w, v, cc);
    }
}

void solve() {
    vector<int> arr;
    for(int i = 1; i <= n; i++)
        arr.push_back(degree[i]);
    sort(arr.begin(), arr.end());
    max_c = arr[n - k - 1];
    cout << max_c << "\n";
    dfs(1, -1, -1);
    for(int i = 1; i < n; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T--) {
        cin >> n >> k;
        graph.assign(n + 1, {});
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back({w, i}), graph[w].push_back({v, i});
            degree[v]++, degree[w]++;
        }
        solve();
    }
};