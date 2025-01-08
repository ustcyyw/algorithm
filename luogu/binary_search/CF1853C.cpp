/**
 * @Time : 2025/1/7-9:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1853C 1800 二分答案
 */
/*
  * 最小的元素 前面的都要被删除了 而且自己不能被删 如果二分中 该元素刚好被删怎么办？
  * 可以找小于val的数有0个的最大的val
  * 那么这样某一次二分中val刚好被删了并且校验通过了
  * 那么小于val + 1的数也有0个 并且val + 1可能没被删 还是被删就可能继续会去查找val + 2
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, a[N];
// 一共有val个数要被删除 那么找到刚好 a[i] <= val的最大值
// a[1,i]指定的位置的数就被删除 刚好删了i个 还剩的 val - i 个数排在了前面 继续删除
bool check(ll val) {
    for(int c = k, i = n; c; c--) {
        while(i >= 1 && a[i] > val)
            i--;
        val -= i;
        if(val <= 0) return true;
    }
    return false;
}

void solve() {
    ll lo = 1, hi = 4e10 + 5;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(check(mid - 1)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        solve();
    }
};