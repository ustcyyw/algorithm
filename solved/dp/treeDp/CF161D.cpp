/**
 * @Time : 2025/1/9-11:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 注意到k只有500，可以针对每个结点 计算这个子树中经过这个点的长度为k的路径数目
  * 枚举这个结点将路径分割出来的其中一侧的长度i，那么另外一侧的长度为k-i
  * cnt[v][i] : 与结点v距离为i的子结点的个数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50000 + 5, mod = 998244353;
int T, n, k, cnt[N][501];
ll ans = 0;
vector<vector<int>> graph;

void dfs(int v, int f) {
    cnt[v][0] = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
        for(int i = 1; i <= k; i++)
            ans += (ll)cnt[w][i - 1] * cnt[v][k - i];
        for(int i = 1; i <= k; i++)
            cnt[v][i] += cnt[w][i - 1];
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> k;
        graph.assign(n + 1, {});
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(1, -1);
        cout << ans;
    }
};