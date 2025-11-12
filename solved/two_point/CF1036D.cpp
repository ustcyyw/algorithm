/**
 * @Time : 2025/5/6-10:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1036D 1600 贪心 双指针
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, mod = 998244353;
ll T, n, m, a[N], b[N];

int solve() {
    if(accumulate(a, a + n + 1, 0ll) != accumulate(b, b + m + 1, 0ll))
        return -1;
    int ans = 0;
    for(ll i = 1, j = 1, sum1, sum2; i <= n || j <= m; ) {
        sum1 = a[i++], sum2 = b[j++];
        while(sum1 != sum2) {
            if(sum1 > sum2) sum2 += b[j++];
            else sum1 += a[i++];
        }
        ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        cin >> m;
        for(int i = 1; i <= m; i++)
            cin >> b[i];
        cout << solve();
    }
}