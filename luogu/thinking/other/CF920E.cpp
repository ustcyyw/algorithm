/**
 * @Time : 2025/3/20-11:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF920E 2100 思维 复杂度分析 并查集
 */
/*
  * 删除了m条边 有n个点 那么至少有一个点 删除的边数量 <= m / n
  * 反证：所有点删除的边的数量都 > m / n, 那么总共删除的边 > m 就矛盾了
  *
  * 那么就假设删除边最少的点 刚好删除了 m / n 条，这个分量叫g1
  * 删除一条边 最多能让一个点不在g1中 最多有 m / n 个点不在g1
  *
  * 对于不在g1中的点 暴力枚举所有边（除了已经被删的）进行分量的连通
  * 每个点最多枚举n次 最多有m / n 个点需要枚举 因此总共最多枚举了m次
  *
  * 当前不在g1中的点的所有边都被枚举了 这些点要么被纳入g1 要么就在别的分量中
  * 最终不在g1的点 与g1无关 所以g1中的点不进行枚举是无所谓的
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, mod = 1e9 + 7;
int T, n, m;
set<int> no[N];

struct UF {
    vector<int> id;
    UF(int total) {
        for(int i = 0; i <= total; i++)
            id.push_back(i);
    }

    int find(int p) {
        return id[p] == p ? p : id[p] = find(id[p]);
    }

    void connect(int p, int q) {
        p = find(p), q = find(q);
        if(p == q) return;
        id[p] = q;
    }
};

void solve() {
    // 找到删除边最少的点 将其直接相连点的点先放到同一分量
    int base = 1;
    for(int i = 2; i <= n; i++) {
        if(no[i].size() < no[base].size())
            base = i;
    }
    UF uf(n);
    for(int i = 1; i <= n; i++) {
        if(!no[base].count(i))
            uf.connect(base, i);
    }
    // 枚举和base现在还不在同一个分量中的结点 最多 m / n 个
    for(int i = 1; i <= n; i++) {
        if(uf.find(base) == uf.find(i)) continue;
        for(int j = 1; j <= n; j++) {
            if(!no[i].count(j)) uf.connect(i, j);
        }
    }
    map<int, int> map;
    for(int i = 1; i <= n; i++)
        map[uf.find(i)]++;
    vector<int> arr;
    for(auto& p : map)
        arr.push_back(p.second);
    sort(arr.begin(), arr.end());
    cout << arr.size() << "\n";
    for(int num : arr)
        cout << num << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, v, w; i <= m; i++) {
        cin >> v >> w;
        no[v].insert(w), no[w].insert(v);
    }
    solve();
}