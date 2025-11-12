/**
 * @Time : 2024/11/10-3:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1927F 并查集 图论 dfs
 */
 /*
  * 并查集考察图中的成环问题
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 4e2;
int T, n, m, b, tx, ty, marked[N];
vector<int> ans;
vector<vector<int>> edges, graph;

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    bool connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return true;
        id[p] = q;
        return false;
    }
};

void dfs(int v, int f, vector<int>& temp) {
    marked[v] = true;
    if(!ans.empty()) return;
    for(int w : graph[v]) {
        if(w == tx && v == ty && temp.size() > 1) {
            ans = temp;
            return;
        }
        if(w == f || marked[w] || (temp.size() == 1 && v == tx && w == ty)) continue;
        temp.push_back(w);
        dfs(w, v, temp);
        temp.pop_back();
    }
}

void solve() {
    sort(edges.begin(), edges.end());
    UF uf(n + 1);
    for(int i = m - 1; i >= 0; i--) {
        int p = edges[i][1], q =  edges[i][2];
        bool flag = uf.connect(p, q);
        if(flag) b = edges[i][0], tx = p, ty = q;
    }
    vector<int> temp(1, tx);
    dfs(tx, -1, temp);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        edges = {}, ans = {}, graph.assign(n + 1, {});
        fill(marked, marked + n + 1, 0);
        for(int i = 1, x, y, w; i <= m; i++) {
            cin >> x >> y >> w;
            edges.push_back({w, x, y, i});
            graph[x].push_back(y), graph[y].push_back(x);
        }
        solve();
        cout << b << " " << ans.size() << "\n";
        for(int num : ans)
            cout << num << " ";
        cout << "\n";
    }
};