/**
 * @Time : 2025/1/1-9:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 假设l的最高位是b1，r的最高位是b2， b2 >= b1
  * 如果 b2 > b1：在b2位上 让a取1，b取0，剩下的所有位a取0 b取1
  * 就能保证 a <= r， 且b >= l
  * 如果b2 = b1：在l和r相同的位上 a和b只能取相同的值
  * 直到第一个l和r不相同的位 一定是 r = 1, l = 0, 让a取1, b取0
  * 接下就可以无脑让a取0，b取1
  *
  * 两种情况合起来写 就是找到第一位l和r不同的位 让a取1，b取0
  * 剩下的位无脑让a取0即可 b取1。
  * 再化简就是找到l和r不同的第一位i 然后返回 (1 << (i + 1)) - 1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, l, r;

ll solve() {
    for(int i = 63; i >= 0; i--) {
        ll t = 1ll << i, tl = t & l, tr = t & r;
        if(tl != tr) return (1ll << (i + 1)) - 1;
    }
    return 0; // l = r 的情况
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> l >> r;
        cout << solve();
    }
};