/**
 * @Time : 2024/9/18-4:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1862D 数学 + 二分
 */
 /*
  * 两个球为一组 给定了组数 最少需要多少个球刚好能凑出来
如果是n个不同的球 一共能组合出 n * (n - 1) / 2


n = 19 有 171
179 就需要+8个同色的 27

n = 20 有 190就超了
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, num;

void solve() {
    ll lo = 2, hi = 2e9;
    while(lo < hi) {
        ll n = (lo + hi + 1) >> 1, total = n * (n - 1) / 2;
        if(total > num) hi = n - 1;
        else lo = n;
    }
    cout << lo + num - lo * (lo - 1) / 2 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> num;
        solve();
    }
};