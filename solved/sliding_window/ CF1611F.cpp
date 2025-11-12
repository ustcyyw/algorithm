/**
 * @Time : 2024/7/22-10:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1611F 滑动窗口
 */
/*
 * 枚举左端点 对于确定的左端点 lo 找到最大的hi 使得 s + sum[lo, hi - 1] < 0
 * 并且 s + sum[lo, i] >= 0, for i in range[lo, hi] 成立
 * 这样就是一个可能的答案
 * 然后要移动lo = lo + 1，记此时的左边界为lt
 * 如果nums[lo] > 0, s + sum[lo, hi - 1] < 0 依旧成立
 * 但是 s + sum[lo, i] >= 0, for i in range[lo, hi] 不一定成立
 * 但这个错误的情况 比正确答案的区间长度更小 不会被记录 不影响正确性
 * 在右移动lo的过程中，会有出现s + sum[lo, hi - 1] >= 0的时候
 * 注意s + sum[lt, hi - 1]是第一次出现 < 0 的区间和， s + sum[lt, hi - 1] < s + sum[lt, i]
 * 此时s + sum[lo, hi - 1] >= 0，也意味着 s + sum[lo, i] > 0 也都成立 这是新的可行的答案
 * 因此要右移lo保证 s + sum[lo, hi - 1] >= 0
 *
 * 如果sum[lo] <= 0, s + sum[lo, hi - 1] < 0 不一定成立
 * 并且 s + sum[lo, i] >= 0, for i in range[lo, hi] 成立
 * 但这肯定是可以满足条件但一个子数组 它长度小于正确答案 不会被记录
 *
 * 因此可以使用滑动窗口 右移hi 保证窗口内的和 + s >= 0
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, s;
ll nums[N];

void solve() {
    int ans = 0, l = -1, r = -1;
    ll sum = 0;
    for(int lo = 1, hi = 1; hi <= n; hi++) {
        sum += nums[hi];
        while(sum + s < 0)
            sum -= nums[lo++];
        int len = hi - lo + 1;
        if(len > ans) ans = len, l = lo, r = hi;
    }
    if(ans == 0) cout << "-1\n";
    else cout << l << " " << r << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> s;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};