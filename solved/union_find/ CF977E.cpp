/**
 * @Time : 2024/11/18-4:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF977E 并查集 图论 1500
 */
 /*
  * 成环的分量需要满足
  * 1. 每个节点的度数都为2
  * 2. n个节点就有n条边
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, edges[N][2], degree[N];
vector<int> sz, id, edge_size;

int find(int p) {
    return id[p] = id[p] == p ? p : find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) edge_size[p]++;
    else {
        id[p] = q;
        sz[q] += sz[p], edge_size[q] += edge_size[p] + 1;
        degree[q] = min(degree[q], degree[p]);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T--) {
        cin >> n >> m;
        sz.assign(n + 1, 1), id.assign(n + 1, 0), edge_size.assign(n + 1, 0);
        for(int i = 1; i <= n; i++)
            id[i] = i;
        for(int i = 1, p, q; i <= m; i++) {
            cin >> p >> q;
            edges[i][0] = p, edges[i][1] = q;
            degree[p]++, degree[q]++;
        }
        for(int i = 1; i <= m; i++)
            connect(edges[i][0], edges[i][1]);
        set<int> set;
        for(int i = 1; i <= n; i++) {
            int p = find(i);
            if(sz[p] == edge_size[p] && degree[p] == 2) set.insert(p);
        }
        cout << set.size();
    }
};