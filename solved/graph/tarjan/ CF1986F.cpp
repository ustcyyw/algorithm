/**
 * @Time : 2024/6/26-1:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1986F 图论 tarjan 贪心
 */
 /*
  * 图本来是连通的 那么一共有 base = n(n - 1) / 2个存在路径的点对
  * 要让这样的点对最少 去掉一条边 要能减少点对 肯定是去掉割边
  * 假设去掉割边后两边的结点数量为 cnt1, cnt2, 那么减少的点对数量为 cnt1 * cnt2
  * 并且 cnt2 = n - cnt1
  * 在找割边的意义下 tarjan算法中 父子关系是确定的
  * 因此也可以在递归中维护子结点个数之和
  * 在tarjan算法中找到一条割边就进行一次计算
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, m, tim;
ll base, ans = LONG_LONG_MAX;
vector<vector<int>> graph;

void tarjan() {
    vector<int> dfn(n + 1, -1), low(n + 1, INT_MAX);
    function<int(int, int)> dfs = [&](int v, int f) -> int {
        dfn[v] = low[v] = tim++;
        int cnt = 0, l = 0; // cnt：儿子结点个数; l：v的儿子中最大的low[son]
        for(int w : graph[v]) {
            if(dfn[w] == -1) { // w 还没被访问过，那么它是v的儿子
                int son_cnt = dfs(w, v);
                cnt += son_cnt;
                l = max(l, low[w]);
                low[v] = min(low[v], low[w]);
                if(low[w] > dfn[v]) { // 找到一个桥
                    int ot = n - son_cnt;
                    ll temp = base - (ll)ot * son_cnt;
                    ans = min(ans, temp);
                }
            } else if(w != f) // w被访问过 且不是父结点 更新low[v]
                low[v] = min(low[v], dfn[w]);
        }
        return cnt + 1;
    };
    dfs(1, -1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        graph.assign(n + 1, {});
        tim = 1, base = (ll)n * (n - 1) / 2, ans = base;
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        tarjan();
        cout << ans << "\n";
    }
};