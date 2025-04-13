/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 15, M = 30;
ll n, a[N], b[N], bsa[N], bsb[N], isa[N], isb[N], rsa[N], rsb[N];

ll cal(int i, ll* base1, ll* is, ll* base2, ll* rs) {
    int j = i / 2;
    ll line1 = is[n] - is[j] + j * (base1[n] - base1[j]);
    ll line2 = rs[j + 1] + (j + n) * (base2[n] - base2[j]);
    return line1 + line2;
}

void solve() {
    ll ans = 0, preSum = 0;
    for(int i = 0; i <= 2 * n; i += 2) {
        int j = i / 2;
        ll temp = 0;
        if(j % 2 == 0) temp = cal(i, bsa, isa, bsb, rsb);
        else temp = cal(i, bsb, isb, bsa, rsa);
        ans = max(ans, temp + preSum);
        if(j % 2 == 0) preSum += i * a[j + 1] + (i + 1) * b[j + 1];
        else preSum += i * b[j + 1] + (i + 1) * a[j + 1];
    }
    ans = max(ans, preSum);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        bsa[i] = bsa[i - 1] + a[i];
        isa[i] = isa[i - 1] + (i - 1) * a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        bsb[i] = bsb[i - 1] + b[i];
        isb[i] = isb[i - 1] + (i - 1) * b[i];
    }
    for(int i = n; i >= 1; i--) {
        rsa[i] = rsa[i + 1] + a[i] * (n - i);
        rsb[i] = rsb[i + 1] + b[i] * (n - i);
    }
    solve();
}