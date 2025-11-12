/**
 * @Time : 2024/10/25-4:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2008F 数学
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n;

long long qPow(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = (x % mod) * (x % mod) % mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        long long pre = 0, sum = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            sum = (sum + (num * pre ) % mod) % mod;
            pre = (pre + num) % mod;
        }
        cout << sum * qPow((n * (n - 1) / 2), (ll)(mod - 2)) % mod << "\n";
    }
};