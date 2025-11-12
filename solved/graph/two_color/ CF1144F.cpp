/**
 * @Time : 2024/5/9-4:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1144F 二分图染色
 */
 /*
  * 将无向图变有向图 让路径长度都为1
  * 也就是说同一个结点上的边 不能出现一进一出的情况
  * 那么有的结点得只有出边 有的结点只有进边 二分图
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e9 + 1;
int n, m, flag = 0, color[N];
vector<int> graph[N], edges[N];

void dfs(int v, int c) {
    if(flag) return;
    color[v] = c;
    int oc = c == 2 ? 1 : 2;
    for(int w : graph[v]) {
        if(color[w] != 0) {
            if(color[w] != oc) {
                flag = 1;
                break;
            }
        } else dfs(w, oc);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        edges[i] = {u, v};
        graph[u].push_back(v), graph[v].push_back(u);
    }
    dfs(1, 1);
    if(flag) cout << "NO";
    else {
        cout << "YES\n";
        for(int i = 1; i <= m; i++) {
            cout << (color[edges[i][0]] == 1 ? 0 : 1);
        }
    }
};