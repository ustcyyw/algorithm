/**
 * @Time : 2024/5/23-3:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1249F 树型dp
 */
/*
 * dp[v][i]: 在v点还要向下走 至少 i步才能取一个点的最大值
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 205, mod = 998244353;
int T, n, k, a[N], dp[N][N];

vector<int> graph[N];

void dfs(int v, int f) {
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
    }
    // 取v这个点的情况 那么其所有子结点得向下走至少k步 才能保证取到的点与v距离 > k
    dp[v][0] = a[v];
    for(int w : graph[v])
        if(w != f) dp[v][0] += dp[w][k];
    // 不取v这个点的情况 枚举所取结点最小深度i 除开自身这个点 还剩n-1个点 理论上最大深度为n-1
    for(int i = 1; i < n; i++) {
        for(int son : graph[v]) { // 枚举其中一个子树中取的结点x，dis(x, v) >= i，dis(x, son) >= i - 1
            if(son == f) continue;
            int cnt = dp[son][i - 1];
            for(int o : graph[v]) { // 计算其它子树的贡献
                if(o == son || o == f) continue;
                // 那么其它子树所取结点y 除了dis(y,v) >= i, 那么dis(y,o) >= i - 1
                // 还要求dis(x,y) >= k + 1, dis(x, v) >= i
                // 那么dis(y,v) >= k + 1 - i, dis(y,o) >= k - i
                cnt += dp[o][max(i - 1, k - i)];
            }
            dp[v][i] = max(dp[v][i], cnt);
        }
    }
    for(int i = n - 2; i >= 0; i--)
        dp[v][i] = max(dp[v][i], dp[v][i + 1]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs(1, -1);
    cout << dp[1][0];
};