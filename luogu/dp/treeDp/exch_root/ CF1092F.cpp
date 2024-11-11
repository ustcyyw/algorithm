/**
 * @Time : 2024/4/24-8:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll n, nums[N], sum[N], dv[N], ans = 0, val[N];
vector<int> graph[N];

void dfs1(int v, int f) {
    sum[v] = nums[v];
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v);
        sum[v] += sum[w], dv[v] += sum[w] + dv[w];
    }
}

void dfs2(int v, int f) {
    if(f == -1) val[v] = dv[v];
    else val[v] = (sum[1] - sum[v]) + val[f] - sum[v];
    ans = max(ans, val[v]);
    for(int w : graph[v])
        if(w != f) dfs2(w, v);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    cout << ans;
};