/**
 * @Time : 2025/4/21-5:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2074D 2100 动态规划 区间dp
 */
/*
 * 任意画一个三角形 可以将多边形分为至多3个连续的部分
 * 并且结合数据范围 可以确定是区间dp
 * 那么定义 f(l,r)为 点编号 [l,r] 构成的多边形（i和j也有一条边相连）能得到的最大值
 * 1. 端点l,r是选中的三角形的两个顶点，那么枚举第三个顶点i即可
 * 这样[l+1,i-1],[i+1,r-1]这两个部分继续取三角形 保证了不相交
 * 2. 端点l,r不同时为选中的三角形的两个顶点，那么可以枚举多边形的分割点i
 * 将多边形分为两个部分，在两个部分中再去选择三角形 这样保证了三角形不会相交
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 4e2 + 15;
ll T, n, a[N];
vector<vector<ll>> cache;

ll dfs(int l, int r) {
    if(l + 1 >= r) return 0;
    if(cache[l][r] != -1) return cache[l][r];
    ll ans = 0;
    for(int i = l + 1; i <= r - 1; i++) {
        ans = max(ans, dfs(l + 1, i - 1) + dfs(i + 1, r - 1) + a[l] * a[r] * a[i]);
    }
    for(int i = l; i <= r - 1; i++) {
        ans = max(ans, dfs(l, i) + dfs(i + 1, r));
    }
    return cache[l][r] = ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        cache = vector(n, vector(n, -1ll));
        for(ll i = 0; i < n; i++)
            cin >> a[i];
        cout << dfs(0, n - 1) << "\n";
    }
    return 0;
}