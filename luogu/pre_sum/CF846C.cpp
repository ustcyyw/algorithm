/**
 * @Time : 2025/3/5-9:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF846C 1800 前缀和 前后缀分解
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5000 + 5, P = 13331;
ll n, sum[N];

ll get_sum(int l, int r) {
    r--;
    if(l > r) return 0;
    return sum[r] - sum[l - 1];
}

void solve() {
    ll val = LONG_LONG_MIN, l1, l2, l3;
    for(int j = 1; j <= n + 1; j++) {
        ll v1 = LONG_LONG_MIN, ti;
        for(int i = 1; i <= j; i++) {
            ll vt = get_sum(1, i) - get_sum(i, j);
            if(vt > v1) v1 = vt, ti = i;
        }
        for(int k = j; k <= n + 1; k++) {
            ll vt = get_sum(j, k) - get_sum(k, n + 1);
            if(vt + v1 > val) {
                val = vt + v1;
                l1 = ti, l2 = j, l3 = k;
            }
        }
    }
    cout << l1 - 1 << " " << l2 - 1 << " " << l3 - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        sum[i] = num + sum[i - 1];
    }
    solve();
}