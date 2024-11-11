/**
 * @Time : 2024/9/4-4:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1811F 思维题 找规律
 */
 /*
  * 观察图形得出以下结论：
  * 1. 结点个数刚好都是完全平方数 记 k = sqrt(n)
  * 2. 边的数量刚好是 n + k
  * 3. 刚好有k个度数为4的结点，其余结点 n - k 个度数为2
  * 4. 存在一个由k个度数为4的结点构成的主环
  * 5. 存在k个结点数量为k的 并且每个环中有1个度数为4的结点 其它结点度数为2
  * 这是构成花图的必要条件 满足这5个条件才可能是花图 但是充分性不知道如何证明 盲猜就是冲要条件
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m, k, degree[N];
vector<vector<int>> graph;

// d表示在递归的时候 不走度数为d的点 除非它是起点
bool dfs(int v, int f, int s, int depth, int d) {
    if(v == s && depth != 0) return depth == k;
    for(int w : graph[v]) {
        if(w == f || (degree[w] == d && w != s)) continue;
        return dfs(w, v, s, depth + 1, d);
    }
    return false;
}

bool check() {
    k = sqrt(n);
    if(k * k != n || k + k * k != m) return false;
    int cnt2 = 0, cnt4 = 0;
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 2) cnt2++;
        if(degree[i] == 4) cnt4++;
    }
    if(cnt4 != k || cnt2 != n - k) return false;
    int v = 0;
    for(int i = 1; i <= n; i++) {
        if(degree[i] == 4) {
            v = i;
            if(!dfs(i, -1, i, 0, 4)) return false;
        }
    }
    // 最后还要检查主环 是否是k个度数为4的结点构成的环
    return dfs(v, -1, v, 0, 2);
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        graph.assign(n + 1, {});
        fill(degree, degree + n + 1, 0);
        for(int i = 1, v, w; i <= m; i++){
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
            degree[v]++, degree[w]++;
        }
        cout << (check() ? "YES" : "NO") << "\n";
    }
};