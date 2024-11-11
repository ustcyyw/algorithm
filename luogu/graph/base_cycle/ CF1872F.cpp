/**
 * @Time : 2024/9/20-9:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1872F 基环树
 */
/*
  * 先把依赖关系看作图 每个点的出度是1 是一个基环树深林
  *
  * 对于枝条 肯定是先选择度数为0的点 这样其依赖的点未处理 其值加倍
  *
  * 对于剩下的环 挑选环中一点后 该环就断开成链 处理逻辑同枝条
  * 但是应该先挑选环中最小值结点所指向的结点
  * 这样按枝条逻辑处理的时候 这个点是最后选择的点 其依赖点已经被处理 只有这个最小值没有加倍 总和最优
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, a[N], c[N], degree[N];
vector<int> orders;

void dfs1(int v) {
    orders.push_back(v), degree[v] = -1;
    degree[a[v]]--;
    if(degree[a[v]] == 0) dfs1(a[v]);
}

int dfs2(int v, int s) {
    int w = a[v];
    if(w == s) return v;
    int t = dfs2(w, s);
    return c[t] < c[v] ? t : v;
}

void solve() {
    // 树枝的处理
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) dfs1(i);
    // 找环中的最小结点编号 从该结点的下一个结点按枝条逻辑处理
    for(int i = 1; i <= n; i++) {
        if(degree[i] <= 0) continue;
        int v = dfs2(i, i);
        degree[a[v]] = 0;
        dfs1(a[v]);
    }
    for(int num : orders)
        cout << num << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        orders = {}, fill(degree, degree + n + 1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            degree[a[i]]++;
        }
        for(int i = 1; i <= n; i++)
            cin >> c[i];
        solve();
    }
};