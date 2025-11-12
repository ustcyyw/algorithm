/**
 * @Time : 2025/4/23-11:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2091E 1300 数学 数论 暴力枚举 二分查找
 */
 /*
  * lcm(a,b) = a * b / gcd(a, b)
  * f = lcm/gcd = a * b / (gcd * gcd) = a / gcd * b / gcd
  * f是一个质数，那么a / gcd = 1， b / gcd是一个质数
  * 所以a是b的一个因子， 并且b的另外一个因子是质数
  * 直接暴力枚举a，然后看有哪些质数 * a <= n，满足条件的都可以是b
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e7 + 15, mod = 998244353;
int T, n;

vector<int> prime;
int init = []() {
    vector<int> isPrime(N + 1, 1);
    for(int i = 2; i < N; i++){
        if(isPrime[i] == 0) continue; // 不是素数 跳过
        if((long)i * i >= LONG_LONG_MAX) continue;
        for(int j = i + i; j < N; j += i) // 将素数的所有倍数标记成合数
            isPrime[j] = 0;
    }
    for(int i = 2; i < N; i++)
        if(isPrime[i] == 1) prime.push_back(i);
    return 0;
}();


void solve() {
    ll ans = 0;
    for(int a = 1; a < n; a++) {
        int temp = n / a;
        ans += upper_bound(prime.begin(), prime.end(), temp) - prime.begin();
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n;
        solve();
    }
}