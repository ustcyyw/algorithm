/**
 * @Time : 2025/4/29-1:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1009E 2000 数学 概率论
 */
 /*
  * a1 a2 a3 a4 a5
a1 a1 a2 a3 a4
a1 x  a1 a2 a3
a1 x  x  a1 a2
a1 x  x  x  a1

第5个位置a5的概率，前4个位置都没触发 1/16
第5个位置a4的概率，第1个位置触发，2 3 4位置没有触发 1/16
第5个位置a3的概率，第2个位置触发，3 4位置没有触发 1/8
第5个位置a2度概率，第3个位置触发，4位置没有触发 1/4
第5个位置a1的概率，第4个位置触发 1/2

第四个位置a4的概率, 前3个位置都没有触发 1/8
第四个位置a3的概率，第1个位置触发 第2、3个位置没触发 1/8
第四个位置a2的概率，第2个位置触发 第3个位置没有触发 1/4
第四个位置a1的概率，第3个位置触发 1/2

第三个位置a3的概率，前2个位置都没触发 1/4
第三个位置a2的概率，第2个位置触发，第2个位置没有 1/4
第三个位置a1的概率，第二个位置触发 1/2

第二个位置a2的概率 1/2
第二个位置a1的概率 1/2

第一个位置a1的概率 1

  按照这个例子找规律即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 998244353, inv2=499122177;
ll T, n, a[N];

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    ll ans = a[1], p = 1, sum = 0;
    for(int i = 2; i <= n; i++) {
        p = p * inv2 % mod;
        ans = (ans + a[i - 1] * p % mod + a[i] * p % mod + sum) % mod;
        sum += a[i - 1] * p % mod;
    }
    ans = ans * qPow(2, n - 1) % mod;
    cout << ans;
}