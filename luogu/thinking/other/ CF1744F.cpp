/**
 * @Time : 2024/3/14-5:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * mex = 0的任意数组, mid > mex, 所以不会贡献答案
 *
 * mex = 1的数组，要求包含0，但是不能含有1
 *
 * mex = 2 要含有0 1，且不含有2的任意数组
 * mex值 是实际上的第3大值 那么这些子数组 只要数组长度超过4 mid值就会大于2
 *
 * mex = 3 要含有0 1 2，且不含有3的任意数组
 * mex值是实际上的第四大值 那么这些子数组 只要数组长度超过6 mid值就会大于3
 *
 * 因此发现 在确定mex值的情况下 子数组的最大长度也唯一确定 就是 2 * mex
 * 并且mex值确定 也就固定了子数组的范围 一定要包含的数（所有 < mex的数）确定的边界为[lo, hi]
 * 一定不能包含的数(mex这个数)确定的边界为[l, r]
 * 枚举mex的值，然后看这个mex值下 有哪些子数组满足
 * 1.长度 <= 2 * mex
 * 2.包含了[lo, hi]且是[l, r]的子区间
 * 可以枚举区间的左端点lt，最小值lts = max(l, hi - 2 * mex + 1)，然后确定区间的右边界可以取哪些值。
 * 区间右端点的最大值记为rt = min(r, lt + 2 * mex - 1)，那么右端点的区间为[hi, rt]
 * 对答案的贡献为 ans += rt - hi + 1;
 *
 * 这样的做法会超时 但可以优化 rt = min(r, lt + 2 * mex - 1), 随着lt的增加rt增加或者不变
 * 当 r <= lt + 2 * mex - 1时，即lt >= r - 2 * mex + 1时，rt恒定为r
 * 记 ltt = max(lts, r - 2 * mex + 1), 当lt >= ltt时，rt = r
 *
 * 如果有 ltt <= lo, 那么在lt属于[ltt, lo]时，rt = r，每个lt对答案的贡献都是 r - hi + 1
 * 如果有 ltt - 1 >= lts，那么每个lt属于[lts, min(lo, ltt - 1)]
 * rt = lt + 2 * mex - 1，随着lt的增大而增大，是一个等差数列
 * 一共有m = min(ltt - 1, lo) - lts + 1项
 * 首项为 rt1 = lts + 2 * mex - 1, 尾项为 rt2 = min(ltt - 1, lo) + 2 * mex - 1
 * 对答案对贡献也是等差数列
 * 首项为 a = rt1 - hi + 1， 尾项为 b = rt2 - hi + 1
 * 于是lt属于[lts, min(lo, ltt - 1)]时，对答的总贡献是 (a + b) * m / 2
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
int T, n, nums[N], idx[N];

void solve() {
    ll ans = 1; // 特殊情况mex = n，就是整个数组的情况 这种情况满足mex > mid
    // 枚举mex的值 确定子数组的范围
    for (int mex = 1, lo = idx[0], hi = idx[0]; mex < n; mex++) {
        int index = idx[mex];
        // 子数组长度 <= 2 * mex, 会有mex > mid
        if (index > hi || index < lo) {
            int l = index < lo ? index + 1 : 1, r = index > hi ? index - 1 : n;
            // 考虑枚举子区间左端点 lt， 起点 lts = max(l, hi - 2 * mex + 1)
            for (int lt = max(l, hi - 2 * mex + 1); lt <= lo; lt++) {
                int rt = min(r, lt + 2 * mex - 1);
                ans += rt - hi + 1;
            }
        }
        lo = min(lo, index), hi = max(hi, index);
    }
    cout << ans << "\n";
}

void solve1() {
    ll ans = 1; // 特殊情况mex = n，就是整个数组的情况 这种情况满足mex > mid
    // 枚举mex的值 确定子数组的范围
    for (int mex = 1, lo = idx[0], hi = idx[0]; mex < n; mex++) {
        int index = idx[mex];
        // 子数组长度 <= 2 * mex, 会有mex > mid
        if (index > hi || index < lo) { // 不满足条件说明 mex这个数在维护的区间内，此mex值取不到
            int l = index < lo ? index + 1 : 1, r = index > hi ? index - 1 : n;
            int lts = max(l, hi - 2 * mex + 1), ltt = max(lts, r - 2 * mex + 1);
            if (ltt <= lo) ans += (lo - ltt + 1) * (r - hi + 1);
            if (min(ltt - 1, lo) >= lts) {
                int m = min(ltt - 1, lo) - lts + 1;
                int rt1 = lts + 2 * mex - 1, rt2 = min(ltt - 1, lo) + 2 * mex - 1;
                int a = rt1 - hi + 1, b = rt2 - hi + 1;
                ans += (a + b) * m / 2;
            }
        }
        lo = min(lo, index), hi = max(hi, index);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> nums[i];
            idx[nums[i]] = i;
        }
        solve1();
    }
};