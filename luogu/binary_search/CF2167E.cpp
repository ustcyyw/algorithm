/**
 * @Time : 2025/10/29-12:36
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2167E 1590 二分答案
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k, x, a[N];

bool check(int d) {
    int cnt = 0;
    if(a[1] - d >= 0) cnt += a[1] - d + 1;
    if(a[n] + d <= x) cnt += x - (a[n] + d) + 1;
    for(int i = 1; i < n; i++) {
        int l = a[i] + d, r = a[i + 1] - d;
        if(r >= l) cnt += r - l + 1;
        if(cnt >= k) return true;
    }
    return cnt >= k;
}

void solve(int d) {
    if(d == 0) {
        for(int p = 0; k; k--, p++)
            cout << p << " ";
        return;
    }
    for(int p = 0; a[1] - p >= d && k; k--, p++)
        cout << p << " ";
    for(int i = 1; i < n && k; i++) {
        for(int p = a[i] + d; a[i + 1] - p >= d && k; k--, p++)
            cout << p << " ";
    }
    for(int p = a[n] + d; k; k--, p++)
        cout << p << " ";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> x;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + n + 1);
        int lo = 0, hi = 1e9;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if(check(mid)) lo = mid;
            else hi = mid - 1;
        }
        solve(lo);
        cout << "\n";
    }
}