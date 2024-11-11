/**
 * @Time : 2024/9/3-4:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P5043 树hash
 */
/*
  * 如果树是给定边来描述 意味着结点顺序是可调的 树结构和结点存储顺序无关
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int m1 = 998244353, m2 = 19260817, N = 2e5 + 5;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const ull rnd = rng(); // 取一个随机数
ull h[N]; // h[i]: 结点i这棵子树对应的hash值
int T, n;
vector<vector<int>> graph; // 描述树结构
map<ull, int> mp;

// 单一值参与计算hash的映射函数
ull g(ull x) {
    return x * x * x * m1 + m2 + rnd;
}
/*
 * 计算某棵树的hash_code
 */
void dfs(int v, int f) {
    h[v] = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
        h[v] += g(h[w]);
    }
}
// 本题为无根树 所以必须将每个结点作为根去计算hash值 看是否已经出现过
int cal(int t) {
    int id = INT_MAX;
    for(int i = 1; i <= n; i++) {
        fill(h, h + n + 1, 1);
        dfs(i, -1);
        ull code = h[i];
        if(!mp.count(code)) mp[code] = t;
        id = min(id, mp[code]);
    }
    return id;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    for(int t = 1; t <= T; t++) {
        cin >> n;
        graph.assign(n + 1, {});
        for(int i = 1, father; i <= n; i++) {
            cin >> father;
            if(father != 0) graph[i].push_back(father), graph[father].push_back(i);
        }
        cout << cal(t) << "\n";
    }
};