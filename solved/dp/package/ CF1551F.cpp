/**
 * @Time : 2024/7/12-3:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1551F 暴力枚举 背包dp
 */
/*
 * 如果k = 2 特判 任意两点都满足答案 直接返回 n * (n - 1) / 2;
 *
 * n比较小 任意两点的距离 <= n - 1
 * 考虑到选择多个点 他们互相的距离相同 一定是一个星形分布
 * 那么星形的中心v是谁 不确定 所以可以枚举
 * 到这个中心v到距离 也不确定 仍然可以枚举
 * 这就需要统计以v为根的 各个枝条上与v距离为d的点 有多少个
 * 将距离为d的点放在一个分组中，每个枝条上距离为d的点可能有0个1个或者多个
 * 为0的忽略，多个的只能选其中一个
 * 这是个背包dp 但是有权重
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2005, mod = 1e9 + 7;
typedef long long ll;
int T, n, k;
ll ans;
vector<int> graph[105];

void merge(vector<int>& res, vector<int>& temp, int i) {
    for(; i < n; i++)
        res[i] += temp[i];
}

void add(unordered_map<int, vector<int>>& map, vector<int>& temp, int i) {
    for(; i < n; i++) {
        if(temp[i] > 0) map[i].push_back(temp[i]);
    }
}

void cal(vector<int>& arr) {
    int m = arr.size();
    vector<vector<ll>> dp(m + 1, vector(k + 1, 0ll));
    dp[0][0] = 1;
    for(int i = 1; i <= m; i++) {
        dp[i][0] = 1;
        for(int j = 1; j <= min(i, k); j++) {
            dp[i][j] = dp[i - 1][j] + (dp[i - 1][j - 1] * arr[i - 1]) % mod;
            dp[i][j] %= mod;
        }
    }
    ans = (ans + dp[m][k]) % mod;
}

vector<int> dfs(int v, int f, int depth) {
    vector<int> res(n, 0);
    res[depth] = 1;
    unordered_map<int, vector<int>> map;
    for(int w : graph[v]) {
        if(w == f) continue;
        vector<int> temp = dfs(w, v, depth + 1);
        if(f != -1) merge(res, temp, depth);
        else add(map, temp, depth);
    }
    if(f == -1) {
        for(auto& p : map) {
            if(p.second.size() >= k)
                cal(p.second);
        }
    }
    return res;
}

ll solve() {
    if(k == 2) return n * (n - 1) / 2;
    ans = 0;
    for(int i = 1; i <= n; i++)
        dfs(i, -1, 0);
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        memset(graph, {}, sizeof(graph));
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cout << solve() << "\n";
    }
};