/**
 * @Time : 2024/2/6-12:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 二分+前缀和
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
int T, n, m, q, range[N][2], times[N], sum[N];

bool check(int t) {
    memset(sum, 0, sizeof(sum));
    for(int i = 1; i <= t; i++)
        sum[times[i]] = 1;
    for(int i = 1; i <= n; i++)
        sum[i] += sum[i - 1];
    for(int i = 1; i <= m; i++) {
        int l = range[i][0], r = range[i][1];
        if(sum[r] - sum[l - 1] > (r - l + 1) / 2) return true;
    }
    return false;
}

void solve() {
    int lo = 1, hi = q + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << (lo == q + 1 ? -1 : lo) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= m; i++)
            cin >> range[i][0] >> range[i][1];
        cin >> q;
        for(int i = 1; i <= q; i++)
            cin >> times[i];
        solve();
    }
};