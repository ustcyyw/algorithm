/**
 * @Time : 2024/11/26-2:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1933E 二分查找 数学 1500
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, q, l, u, sum[N] = {0};

ll cal(int r) {
    if(r > n) return LONG_LONG_MIN;
    int cnt = sum[r] - sum[l - 1];
    return (ll)cnt * (u - cnt + 1 + u) / 2;
}

void solve() {
    int lo = l, hi = n;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(sum[mid] - sum[l - 1] >= u) hi = mid - 1;
        else lo = mid;
    }
    cout << (cal(lo) >= cal(lo + 1) ? lo : lo + 1) << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            sum[i] = sum[i - 1] + num;
        }
        cin >> q;
        for(int i = 1; i <= q; i++) {
            cin >> l >> u;
            solve();
        }
        cout << "\n";
    };
};