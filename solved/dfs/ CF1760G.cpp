/**
 * @Time : 2024/6/2-2:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1760G dfs
 */
 /*
  * 注意只能使用最多一次跳过操作
  * 从a出发走的路径和视为前缀 从b出发走的路径和为后缀
  * 通过一次条约操作将前缀和后缀连起来
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, a, b;
vector<vector<vector<int>>> graph;
set<int> suf, pre;

void dfs1(int x, int v, int f, set<int>& st) {
    if(f != -1) st.insert(x);
    for(auto& edge : graph[v]) {
        if(edge[0] == f) continue;
        int w = edge[0], d = edge[1];
        if(w != b || (d ^ x) == 0) // 下一个结点不是b 或者下一个结点是b但是路径和已经为0
            dfs1(d ^ x, w, v, st);
    }
}

bool solve() {
    dfs1(0, a, -1, pre);
    pre.insert(0); // 从a出发可以直接跳过 此时路径和为0
    dfs1(0, b, -1, suf);
    for(int num : pre) {
        if(suf.count(num))
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> a >> b;
        suf.clear(), pre.clear();
        graph.assign(n + 1, {});
        for(int i = 1, v, w, d; i <= n - 1; i++) {
            cin >> v >> w >> d;
            graph[v].push_back({w, d}), graph[w].push_back({v, d});
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};