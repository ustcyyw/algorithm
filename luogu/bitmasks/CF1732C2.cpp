/**
 * @Time : 2025/1/17-5:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1732C2 2100 思维 位运算 暴力枚举
 */
/*
  * sum是实打实的加 但是xor操作最多也就刚好加上去 也就是说取满整个区间 值一定最优
  * f1 = f2, 假设f2是更小的区间
  * sum1 - xor1 = sum2 - xor2
  * sum1 - sum2 = xor1 - xor2
  * 区间和的差值 刚好是异或带来的差值 也就是说 这个异或是实打实的加上去了
  * 说明这些数（f1比f2多的那些数）之间1的位置是 不重叠的
  * 总共只有32位1，最多也就32个数字能不重叠了 因此可以暴力枚举
  *
  * 枚举左边可以删除的数字的区间，以及右边可以删除的数字的区间
  * 要满足的条件是，删除的这些数字 异或和 = 数字和
  * 要注意特殊值0，0是肯定可以删除的，用nxt[i], pre[i]记录当前数字的下一个/上一个非0值
  * 这样在遇到0的时候就可以快速略过0
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, q, l, r, a[N], val[N], sum[N], nxt[N], pre[N];

void solve() {
    if(nxt[l] > r) { // 当前查询区间全是0的情况
        cout << l << " " << l << "\n";
        return;
    }
    l = nxt[l], r = pre[r];
    int len = 0, rl = l, rr = r;
    int s = sum[r] - sum[l - 1], x = val[r] ^ val[l - 1], t = s - x;
    // 删除的区间[l,i],[j,r]
    for(int i = l - 1; i <= r; i = nxt[i] == i ? i + 1 : nxt[i]) {
        int s1 = sum[i] - sum[l - 1], x1 = val[i] ^ val[l - 1];
        if(s1 != x1) break;
        for(int j = r + 1; j >= l; j = pre[j] == j ? j - 1 : pre[j]) {
            int s2 = sum[r] - sum[j - 1], x2 = val[r] ^ val[j - 1];
            if(s2 != x2 || (s1 + s2 != (x1 ^ x2))) break;
            // 要保证删除两边后 中间剩余区间依旧满足f值为最大值
            if(t == s - s1 - s2 - (x ^ x1 ^ x2)) {
                int ri = nxt[i] == i ? i : nxt[i] - 1, rj = pre[j] == j ? j : pre[j] + 1;
                int tl = ri - l + 1 + r - rj + 1;
                if(tl > len) len = tl, rl = ri + 1, rr = rj - 1;
            }
        }
    }
    if(rl > rr) rl = l, rr = l;
    cout << rl << " " << rr << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> q;
        int j = 0;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            if(a[i] > 0) j = i;
            pre[i] = j;
            sum[i] = sum[i - 1] + a[i], val[i] = val[i - 1] ^ a[i];
        }
        pre[n + 1] = j;
        j = n + 1;
        for(int i = n; i >= 1; i--) {
            if(a[i] > 0) j = i;
            nxt[i] = j;
        }
        nxt[0] = j;
        for(int i = 1; i <= q; i++) {
            cin >> l >> r;
            solve();
        }
    }
};