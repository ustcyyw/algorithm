/**
 * @Time : 2025/1/2-8:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2026B 1300 暴力枚举 前后缀分解
 */
 /*
  * 如果是偶数个点 借助外面一个点 就会导致剩下奇数个点 无法完成涂黑 因此不能借助外面的点
  * 如果是奇数个点 可以有一个点借助外面的点 并且借助的这个点 是奇数位置的点
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2000 + 5, mod = 998244353;
ll T, n, nums[N], preMax[N];

ll solve() {
    if(n == 1) return 1;
    for(int i = 1; i + 1 <= n; i += 2) {
        preMax[i] = nums[i + 1] - nums[i];
        if(i - 2 >= 1) preMax[i] = max(preMax[i], preMax[i - 2]);
    }
    if(n % 2 == 0) return preMax[n - 1];
    ll k = LONG_LONG_MAX, suf = 0;
    for(int i = n; i >= 1; i -= 2) {
        k = min(k, max(suf, preMax[i - 2]));
        suf = max(suf, nums[i] - nums[i - 1]);
    }
    return k;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};