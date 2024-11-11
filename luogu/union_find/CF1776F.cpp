/**
 * @Time : 2024/6/4-10:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1776F 并查集 构造
 */
 /*
  * 同一家公司 允许其连通n-1个结点 那么就是连通分量合并n-2次
  * 剩下的再交给另外一家公司来进行 直到所有边都已经确定经营情况
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 55, MV = 1e9;
typedef long long ll;
int T, n, m, k, ans[2500];
map<int, vector<int>> edges;

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    bool is_connect(int p, int q) {
        return find(p) == find(q);
    }

    void connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return;
        id[p] = q;
    }
};

void solve() {
    while(!edges.empty()) {
        k++;
        int cnt = 0;
        UF uf(n);
        vector<int> remove;
        for(auto& p : edges) {
            int idx = p.first, x = p.second[0], y = p.second[1];
            bool flag = uf.is_connect(x, y);
            if(!flag && cnt < n - 2) { // 没有连通 并且连通次数 < n - 2的 仍然可以连通
                uf.connect(x, y), cnt++;
                flag = true;
            }
            // 原本就是连着的 或者当前刚连通的 这些边可以标记为同一个公司
            if(flag) ans[idx] = k, remove.push_back(idx);
        }
        for(int idx : remove)
            edges.erase(idx);
    }
    cout << k << "\n";
    for(int i = 1; i <= m; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        k = 0, edges = {};
        for(int i = 1, x, y; i <= m; i++) {
            cin >> x >> y;
            edges[i] = {x, y};
        }
        solve();
    }
};