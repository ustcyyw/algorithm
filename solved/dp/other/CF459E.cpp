/**
 * @Time : 2025/1/21-6:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF459E 1900 排序 动态规划 刷表法
 */
 /*
  * 类似于生成树 先让短的边生长 不断记录每个点作为终点的最长路径
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 3e5 + 5, mod = 998244353, M = 20;
int T, n, m, len[N];
map<int, vector<vector<int>>> mp;

void solve() {
    for(auto& p : mp) {
        map<int, int> temp;
        vector<vector<int>>& edges = p.second;
        for(auto& edge : edges) {
            int a = edge[0], b = edge[1];
            temp[b] = max(temp[b], len[a] + 1);
        }
        for(auto& [node, l] : temp)
            len[node] = max(len[node], l);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
        ans = max(ans, len[i]);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 1, a, b, w; i <= m; i++) {
            cin >> a >> b >> w;
            mp[w].push_back({a, b});
        }
        solve();
    }
};