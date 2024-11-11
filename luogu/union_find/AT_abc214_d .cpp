/**
 * @Time : 2023/8/9-3:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
int n, ids[N], sz[N];

int find(int p) {
    if(ids[p] == p) return p;
    return ids[p] = find(ids[p]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        ids[i] = i, sz[i] = 1;
    vector<vector<int>> edges;
    for(int i = 1, a, b, w; i < n; i++) {
        cin >> a >> b >> w;
        edges.push_back({w, a, b});
    }
    sort(edges.begin(), edges.end());
    long long res = 0;
    for(vector<int>& edge : edges) {
        int p = find(edge[1]), q = find(edge[2]), w = edge[0];
        int n1 = sz[p], n2 = sz[q];
        res += (long long)n1 * n2 * w;
        sz[p] += sz[q], ids[q] = p;
    }
    cout << res << endl;
}