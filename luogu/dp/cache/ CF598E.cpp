/**
 * @Time : 2024/4/2-11:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * n * m 的巧克力 要拿到总面积k的巧克力组合
  * 可以枚举分割线 水平 竖直
  * 并且枚举其中一份要得到多少面积的巧克力
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int T, N, M, K, cache[31][31][51];

int init = []() -> int {
    for(int i = 0; i < 31; i++) {
        for(int j = 0; j < 31; j++)
            fill(cache[i][j], cache[i][j] + 51, -1);
    }
    return -1;
}();

int dfs(int n, int m, int k) {
    if(k == 0 || k == n * m) return 0;
    if(n > m) swap(n, m);
    if(cache[n][m][k] != -1) return cache[n][m][k];
    int res = INT_MAX;
    for(int i = 1; i < n; i++) { // 枚举水平的分割线
        int add = m * m;
        for(int c = max(0, k - (n - i) * m); c <= min(k, m * i); c++)
            res = min(res, add + dfs(i, m, c) + dfs(n - i, m, k - c));
    }
    for(int i = 1; i < m; i++) { // 枚举竖直的分割线
        int add = n * n;
        for(int c = max(0, k - (m - i) * n); c <= min(k, n * i); c++)
            res = min(res, add + dfs(i, n, c) + dfs(m - i, n, k - c));
    }
    return cache[n][m][k] = res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> N >> M >> K;
        cout << dfs(N, M, K) << "\n";
    }
};