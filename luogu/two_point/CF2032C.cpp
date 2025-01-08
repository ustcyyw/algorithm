/**
 * @Time : 2025/1/7-9:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2032C 1400 排序 双指针
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, a[N];

void solve() {
    sort(a + 1, a + n + 1);
    int ans = INT_MAX;
    for(int i = n - 1, j = n; i >= 1; j--) {
        while(i >= 1 && a[i] + a[i + 1] > a[j])
            i--;
        ans = min(ans, n - j + i);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        solve();
    }
};