/**
 * @Time : 2024/9/5-11:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1216D
 */
 /*
  * a中的最大值就是x的值
  * 做差 求gcd
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, x, nums[N];

void solve() {
    ll z = x - nums[1], y = 0;
    for(int i = 1; i <= n; i++)
        z = gcd(z, x - nums[i]);
    for(int i = 1; i <= n; i++)
        y += (x - nums[i]) / z;
    cout << y << " " << z;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T-- > 0) {
        cin >> n;
        x = -1;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            x = max(x, nums[i]);
        }
        solve();
    }
};