/**
 * @Time : 2024/4/23-12:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 计算贡献度
  * 对于a的某一位 b相应的该位及其更高位的1 在计算过程中都会与这一位相与为1，都会对答案有贡献
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll n, m, p[N], sum[N];
string a, b;

int init = []() -> int {
    p[0] = 1;
    for(ll i = 1; i < N; i++)
        p[i] = p[i - 1] * 2 % mod;
    return 0;
}();
// 高位补0
void fill(string& s, int cnt) {
    while(cnt-- > 0)
        s = "0" + s;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    cin >> a >> b;
    int diff = m - n, k = max(n, m);
    if(diff > 0) fill(a, diff);
    else if(diff < 0) fill(b, -diff);
    for(int i = k - 1; i >= 0; i--)
        sum[i] = b[i] - '0' + sum[i + 1];
    ll ans = 0;
    for(int i = k - 1, j = 0; i >= 0; i--, j++) {
        if(a[i] == '0') continue;
        ll cnt = sum[0] - sum[i + 1];
        ans = (ans + cnt * p[j] % mod) % mod;
    }
    cout << ans;
};