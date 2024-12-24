/**
 * @Time : 2024/12/23-11:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1873F 1300 双指针
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k, h[N], a[N];

void solve() {
    int ans = a[1] <= k ? 1 : 0, sum = a[1];
    for(int lo = 1, hi = 2; hi <= n; ) {
        if(h[hi - 1] % h[hi] == 0) sum += a[hi++];
        else lo = hi, hi++, sum = a[lo];
        while(sum > k) sum -= a[lo++];
        if(lo == n + 1) continue;
        if(lo == hi) sum = a[lo], hi++, ans = max(ans, a[lo] <= k ? 1 : 0);
        else ans = max(ans, hi - lo);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> h[i];
        solve();
    }
};