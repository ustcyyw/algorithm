/**
 * @Time : 2024/9/25-9:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1907D 二分答案
 */
 /*
  * k越大 可选的落点越多 越容易通关
  * 固定k的时候 考虑落点的范围与指定区间是否相交
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, ls[N], rs[N];

bool check(int d) {
    int l = 0, r = 0;
    for(int i = 1; i <= n; i++) {
        int lo = l - d, hi = r + d;
        if(hi < ls[i] || lo > rs[i]) return false;
        l = max(ls[i], lo), r = min(rs[i], hi);
    }
    return true;
}

void solve() {
    int lo = 0, hi = 1e9 + 5;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> ls[i] >> rs[i];
        solve();
    }
};