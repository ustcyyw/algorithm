/**
 * @Time : 2025/10/29-23:23
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2167G 1501 动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 8005, mod = 1e9 + 7;
ll T, n, c[N], a[N], pre[N], dp[N];
vector<int> pos;

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}


void solve() {
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    int m = pos.size();
    fill(pre, pre + m, 0);
    for(int i = 1; i <= n; i++) {
        int idx = find(a[i]);
        for(int j = 0; j < m; j++) {
            dp[j] = pre[j] + (idx != j ? c[i] : 0);
            if(j > 0) dp[j] = min(dp[j - 1], dp[j]);
        }
        swap(pre, dp);
    }
    cout << pre[m - 1] << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        pos = {};
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            pos.push_back(a[i]);
        }
        for(int i = 1; i <= n; i++)
            cin >> c[i];
        solve();
    }
}