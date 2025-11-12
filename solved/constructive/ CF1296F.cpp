/**
 * @Time : 2024/6/19-8:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1296F 构造
 */
 /*
  * 有点离线查询的思想
  * 两点之间的风景值确定后 这亮点之间的边 都不能是更小的风景值了
  * 因此先从最大的风景值入手 将这些边进行赋值
  * 更小的风景值对应的一系列边不能与已经赋值的边冲突
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 5005, T = 1e4;
typedef long long ll;
int n, m, val[N];
vector<int> graph[N];
vector<vector<int>> p;
map<int, int> mp;

bool dfs(vector<int> &edges, int v, int f, int t) {
    if (v == t) return true;
    for (int w: graph[v]) {
        if (w == f) continue;
        if (dfs(edges, w, v, t)) {
            int key = max(w, v) * T + min(w, v);
            edges.push_back(mp[key]);
            return true;
        }
    }
    return false;
}

bool check(vector<int> &edges, int g) {
    bool flag = false;
    for(int id : edges) {
        if(val[id] == 0 || val[id] == g) {
            val[id] = g, flag = true;
        }
    }
    return flag;
}

bool solve() {
    vector<int> edges;
    for (int i = m - 1; i >= 0; i--) {
        edges.assign(0, 0);
        int a = p[i][0], b = p[i][1], g = p[i][2];
        dfs(edges, a, -1, b);
        if(!check(edges, g)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for (int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        if (v < w) swap(v, w);
        mp[v * T + w] = i;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    cin >> m;
    for (int i = 1, a, b, g; i <= m; i++) {
        cin >> a >> b >> g;
        p.push_back({a, b, g});
    }
    sort(p.begin(), p.end(), [](auto &a, auto &b) -> bool { return a[2] < b[2]; });
    if(!solve()) cout << "-1";
    else {
        for(int i = 1; i < n; i++)
            cout << (val[i] == 0 ? (int)1e6 : val[i]) << " ";
    }
};