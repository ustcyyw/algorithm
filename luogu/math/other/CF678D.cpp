/**
 * @Time : 2025/2/16-9:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF678D 1700 数学 找规律 快速幂
 */
 /*
  * g1 = f(g0) = f(x) = ax + b;
  * g2 = f(g1) = a(ax + b) + b = a^2x + ab + b
  * g3 = f(g2) = a(a^2x + ab + b) + b = a^3x + a^2b + ab + b
  * g4 = f(g3) = a(a^3x + a^2b + ab + b) + b = a^4x + a^3b + a^2b + ab + b
  * = a^4x + b * (a^3 + a^2 + a + 1)
  * x * a ^ n + b * sum
  * 其中sum是 等比数列求和 公比为a，项数为n 首项为1
  * 注意使用求和公式的时候 a = 1单独处理，求和结果就是n
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 1e9 + 7;
ll T, n, a, b, x;

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

ll cal() {
    if(a == 1) return (x + b * (n % mod) % mod) % mod;
    ll base = qPow(a, n) % mod, inf = qPow(a - 1, mod - 2);
    ll num1 = x * base % mod, num2 = b * (base - 1 + mod) % mod * inf % mod;
    return (num1 + num2) % mod;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> a >> b >> n >> x;
        cout << cal();
    }
};