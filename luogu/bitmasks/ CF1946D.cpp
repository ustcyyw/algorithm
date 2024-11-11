/**
 * @Time : 2024/3/26-10:58 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 位运算 拆位技巧
  * 记各组异或后 再进行组间或的结果记为t
  * t <= x
  * 1.可能存在某一位d，这一位x为1，t为0，高于d的位x和t数位相等 那么x > t
  * 意味着低于d位的数位完全不用处理
  * 2.也可能是对于任意一位 x和t数位相等 那么 x = t
  * 如果将x左移一位再+1，所有数左移一位
  * 那么第二种情况就是取d = 0的时候，就统一到第一种情况中了。
  *
  * 因此 枚举d, 记x高于d位的值是 xt
  * 要保证 高于d的位x和t数位相等，那么每一组的值 (val | tx) == tx 并且满足d位上该组是0
  * 一旦找到这样的条件 就进行一次分组。
  * 注意如果最后一组不满足条件，那么这样的分组不成立 返回-1
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
ll T, n, x, nums[N];
// mask仅保留 > d 的位，mask2保留d的位
ll cal(ll mask1, ll mask2) {
    ll tx = x & mask1, cnt = 0;
    for(ll i = 1, val1 = 0, val2 = 0; i <= n; i++) {
        val1 ^= mask1 & nums[i], val2 ^= mask2 & nums[i];
        if((val1 | tx) == tx && val2 == 0) {
            cnt++;
            val1 = 0, val2 = 0;
        } else if(i == n) cnt = 0;
    }
    return cnt == 0 ? -1 : cnt;
}

void solve() {
    ll full = (1ll << 31) - 1, k = -1;
    for(int i = 30; i >= 0; i--) {
        if((1 << i) & x) {
            ll mask1 = full ^ ((1 << (i + 1)) - 1), mask2 = 1 << i;
            k = max(cal(mask1, mask2), k);
        }
    }
    cout << k << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> x;
        x = (x << 1)+ 1;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            nums[i] = nums[i] << 1;
        }
        solve();
    }
};