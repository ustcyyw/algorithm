/**
 * @Time : 2024/4/4-3:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
int T, n, h[N];

bool check(int t) {
    int pp = 0, p = 0, c = 0;
    for(int i = n; i >= 3; i--) {
        if(c + h[i] < t) return false;
        // 可以给前面的石头 受限于自己有多少 以及自己给了之后还得有t那么多
        int d = min(c + h[i] - t, h[i]) / 3;
        p += d, pp += 2 * d;
        c = p, p = pp, pp = 0;
    }
    return h[1] + p >= t && h[2] + c >= t;
}

void solve() {
    int lo = 1, hi = 1e9;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> h[i];
        solve();
    }
};