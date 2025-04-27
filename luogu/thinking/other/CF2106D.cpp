/**
 * @Time : 2025/4/26-9:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2106D 1467 思维 前后缀分解
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m, a[N], b[N], pre[N], suf[N];

void init() {
    for(int i = 1, j = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        if(j <= m && a[i] >= b[j]) {
            pre[i] = j;
            j++;
        }
    }
    suf[n + 1] = 0;
    for(int i = n, j = m; i >= 1; i--) {
        suf[i] = suf[i + 1];
        if(j >= 1 && a[i] >= b[j]) {
            suf[i] = m - j + 1;
            j--;
        }
    }
}

int solve() {
    init();
    if(pre[n] == m) return 0;
    int ans = INT_MAX;
    for(int i = 0; i <= n; i++) {
        if(pre[i] + suf[i + 1] == m - 1)
            ans = min(ans, b[pre[i] + 1]);
    }
    return ans == INT_MAX ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= m; i++)
            cin >> b[i];
        cout << solve() << "\n";
    }
}