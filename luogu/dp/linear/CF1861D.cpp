/**
 * @Time : 2023/12/15-11:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * in[i]: i为结尾的最长递增序列的起始索引
 * de[i]: i为结尾的最长递减序列的起始索引
 *
 * 考虑一个递增子序列 要与前面元素保持递增关系
 * 如果前面的元素依然为正 一定有 nums[in[i]] < pre 必然需要乘一个数 k
 * （因为已经考虑的是 以i为结尾的最长递增序列）
 * 由于选择乘数是任意的 后续的元素总能乘一个更大的数来通过一次操作大于 nums[i] * k
 * 因此乘数选多大没有意义
 * 如果前面的元素是负数，就已经有nums[in[i]] > pre 不做任何操作
 *
 * 如果将一个递减序列一次就变成递增序列 需要且仅要一次乘负数的操作
 * 但是为了与更之前的元素保持递增关系，要求更之前的元素已经是负数
 * 由于选择的乘数是任意的 假设当前这个递减序列第一个元素变换后为last
 * 总可以调整前面一系列的乘数让 last > pre 但操作次数不变 因此乘数选多大没有意义
 *
 * 综上所述 只需要关注把 nums[i] 当作是递增序列/递减序列的结尾 及 序列前置元素的正负即可
 * 不必关心选择的乘数是多少
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, T, nums[N], in[N], de[N], dp[N][2];

void solve() {
    for(int i = 1, j; i <= n; ) {
        in[i] = i, j = i + 1;
        while(j <= n && nums[j] > nums[j - 1])
            in[j++] = i;
        i = j;
    }
    for(int i = 1, j; i <= n; ) {
        de[i] = i, j = i + 1;
        while(j <= n && nums[j] < nums[j - 1])
            de[j++] = i;
        i = j;
    }
    dp[0][1] = 0, dp[0][0] = -1;
    for(int i = 1; i <= n; i++) {
        int j1 = in[i] - 1, j2 = de[i] - 1;
        // 将nums[i]结尾的子序列当一个递增子序列整体处理 前面可以是正 也可以是负
        dp[i][0] = min(dp[j1][0] + 1, dp[j1][1]);
        // 将nums[i]结尾的子序列当一个递减子序列整理处理 那必须要乘一个负数 且前面必须是一个负数
        dp[i][1] = dp[j2][1] + 1;
    }
    cout << min(dp[n][0], dp[n][1]) << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
}