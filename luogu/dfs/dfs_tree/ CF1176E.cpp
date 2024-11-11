/**
 * @Time : 2024/5/15-10:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 得到一棵dfs搜索树之后 树被分为奇数层和偶数层
  * 这两类中 最少有一类的结点数目 <= n / 2
  * 那么选那一类 另外一类的结点一定与之相邻
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m;
vector<int> arr[2], marked;
vector<vector<int>> graph;

void dfs(int v, int depth) {
    marked[v] = 1;
    arr[depth % 2].push_back(v);
    for(int w : graph[v]) {
        if(marked[w]) continue;
        dfs(w, depth + 1);
    }
}

void solve() {
    dfs(1, 0);
    vector<int>& ans = arr[0].size() <= arr[1].size() ? arr[0] : arr[1];
    cout << ans.size() << "\n";
    for(int num : ans)
        cout << num << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        arr[0].clear(), arr[1].clear();
        cin >> n >> m;
        graph.assign(n + 1, {});
        marked.assign(n + 1, 0);
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        solve();
    }
};