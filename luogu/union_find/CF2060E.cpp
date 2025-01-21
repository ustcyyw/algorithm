/**
 * @Time : 2025/1/21-8:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 在g中有路径的两个点 他们是同一个连通分量的
  * 相当于要让f中的点 连通分量的情况和g中一致 需要先计算g中连通分量的情况
  * 如果f中的边将g中不在一个分量的两点连起来了 那么这条边要删除
  * 如果边将g中在一个分量的的两点连起来了 这条边有效 将所在分量连通
  * 最后看f中的分量数目 如果多余g的分量数目 说明还没连接完成 需要添加边
  * 添加一条边将f的分量减少1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7, R = 26;
int T, n, m1, m2, edge[N][2];

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

int count(UF& uf) {
    set<int> set;
    for(int i = 1; i <= n; i++)
        set.insert(uf.find(i));
    return set.size();
}

void solve(UF& g) {
    int ans = 0;
    UF f(n);
    for(int i = 1; i <= m1; i++) {
        int v = edge[i][0], w = edge[i][1];
        if(!g.is_connect(v, w)) ans++;
        else f.connect(v, w);
    }
    int cntG = count(g), cntF = count(f);
    cout << ans +  cntF - cntG << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> m1 >> m2;
        for(int i = 1; i <= m1; i++)
            cin >> edge[i][0] >> edge[i][1];
        UF g(n);
        for(int i = 1, v, w; i <= m2; i++) {
            cin >> v >> w;
            g.connect(v, w);
        }
        solve(g);
    }
};