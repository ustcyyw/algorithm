/**
 * @Time : 2025/2/11-10:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2065F 思维题
 */
 /*
  * 对于每个数字i 看看是否有一个路径使得这个数字是 m数

1.x的非m数集合 + 非m数集合：还是一个非m数集合
2.x的非m数集合 + m数集合：可能是 也可能不是 但既然已经找到一个了 就没必要考虑合并
3.x的m数集合 + m数集合：一定是 但同上
因此 要么就是找到了单个m数集合 要么就压根不可能通过合并得到
于是找最小m数集合即可 大小为2或者3
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int T, n, node[N];
string ans;
vector<vector<int>> graph;

void solve() {
    for(int i = 1; i <= n; i++) {
        unordered_map<int, int> cnt;
        cnt[node[i]]++;
        for(int w : graph[i])
            cnt[node[w]]++;
        for(auto& [k, c] : cnt)
            if(c >= 2) ans[k] = '1';
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n;
        ans.assign(n + 1, '0'), graph.assign(n + 1, {});
        for(int i = 1; i <= n; i++)
            cin >> node[i];
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        solve();
        cout << ans.substr(1, n) << "\n";
    }
};