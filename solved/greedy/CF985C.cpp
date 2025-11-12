/**
 * @Time : 2025/4/1-9:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF985C 1500 贪心
 */
 /*
  * 最小边mv 一定会成为某个桶的值 那么桶的值就确定了范围 [mv, mv + l]
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 15, M = 30;
int n, k, l, lens[N];

ll solve() {
    int mv = lens[1],  m = n * k;
    int idx = upper_bound(lens + 1, lens + m + 1, mv + l) - lens - 1;
    if(idx < n) return 0;
    ll ans = 0;
    for(int i = idx, left = m - idx; i >= 1; ) {
        if(left >= k - 1) {
            ans += lens[i];
            i--, left -= k - 1;
        } else if(left > 0) {
            ans += lens[i - (k - left) + 1];
            i -= k - left, left = 0;
        } else {
            ans += lens[i - k + 1];
            i -= k;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> l;
    int m = n * k;
    for(int i = 1; i <= m; i++)
        cin >> lens[i];
    sort(lens, lens + m + 1);
    cout << solve();
}