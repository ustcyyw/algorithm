/**
 * @Time : 2024/3/26-9:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
int T, n, k;
vector<int> graph[N];

int dfs(int val, int v, int f, int& ans) {
    int cnt = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        cnt += dfs(val, w, v, ans);
    }
    if(cnt >= val) ans++, cnt = 0;
    return cnt;
}

bool check(int val) {
    int ans = 0;
    dfs(val, 1, -1, ans);
    return ans >= k + 1;
}

void solve() {
    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        memset(graph, {}, sizeof(graph));
        for(int i = 0, v, w; i < n - 1; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        solve();
    }
};
