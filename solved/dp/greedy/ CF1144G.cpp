/**
 * @Time : 2024/5/9-1:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : dp + 状态定义需要从贪心订角度思考
 */
/*
  * 拆分为两个子序列 一个递增 一个递减
  * dp[i][0]: 截止第i个数 nums[i]属于递增序列时 递减序列结尾元素的最大值
  * dp[i][1]:                      递减序列时 递增序列结尾元素的最小值
  * 类似于lis的贪心思路 在序列长度一定时 结尾元素尽可能地小 更有利于序列增长
  * 本题就是在可以拆分为两个序列的情况下 nums[i]在一个序列时 让另外一个序列结尾元素更优
  * 让递增序列结尾最小/递减序列结尾最大 这样更有利于后续元素可以合法放置
  *
  * dp[i][0]: 1和2两种情况如果都出现 取最优
  * 1. 如果nums[i] > nums[i - 1]，那么dp[i - 1][0]
  * 2. nums[i - 1]在递减序列 并且它就是递减序列的结尾元素 此时需要保证 dp[i - 1][1] < nums[i]
  *     也就是nums[i - 1]属于递减序列时 递增序列结尾的元素最小值 < nums[i]
  *     这样才能讲nums[i]放在递增序列中，dp[i][0] = nums[i - 1]
  * 3. 以上两个条件都不满足时 nums[i]无法放在递增序列中 令dp[i][0] = -1，表示这种情况不合法
  *
  * dp[i][1]: 1和2两种情况如果都出现 取最优
  * 1. nums[i] < nums[i - 1], dp[i - 1][1]
  * 2. nums[i - 1]在递增序列 并且它就是递增序列的结尾元素 dp[i - 1][0] > nums[i],
  *     dp[i][1] = nums[i - 1]
  * 3. 以上两个条件都不满足时 dp[i][1] = INT_MAX，表示这种情况不合法
  *
  * 初状态
  * dp[1][0] = INT_MAX, nums[1]放递增序列 递减序列中还没有元素 结尾元素取最大值
  * dp[1][1] = -1, nums[1]放递减序列 递增序列中还没有元素 结尾元素取最小值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e9 + 1;
int n, nums[N], dp[N][2], info[N][2], marked[N];

void std_out() {
    // 如果nums[n]能被放在递增序列 或者递减序列 说明可以完成拆分
    if(dp[n][0] != -1 || dp[n][1] != INT_MAX) {
        cout << "YES\n";
        int idx = n, flag = dp[n][0] != -1 ? 0 : 1;
        while(idx != 0)  {
            marked[idx] = flag;
            flag = info[idx][flag];
            idx--;
        }
        for(int i = 1; i <= n; i++)
            cout << marked[i] << " ";
    } else cout << "NO";
}

void solve() {
    dp[1][0] = INT_MAX, dp[1][1] = -1;
    for(int i = 2; i <= n; i++) {
        int num = nums[i], pre = nums[i - 1];
        // num可以放在pre的下一个元素 pre为递增子序列元素;
        // 或者pre为递减子序列的元素 num放在前置递增序列最小尾元素后面
        if(num > pre || dp[i - 1][1] < num) {
            // pre为递增元素，num可以接上 并且（pre不能作为递减元素 or pre作为递增元素，递减尾元素更大）
            if(num > pre && (dp[i - 1][1] >= num || dp[i - 1][0] >= pre)) {
                dp[i][0] = dp[i - 1][0], info[i][0] = 0;
            } else {
                dp[i][0] = pre, info[i][0] = 1;
            }
        } else dp[i][0] = -1; // 表示这种情况不合法 num没法放在递增序列中
        // dp[i][1]的计算 num为递减尾元素类似
        if(num < pre || dp[i - 1][0] > num) {
            // pre为递减元素 num可以接上 并且（pre不能作为递增元素 or pre为递减元素更好）
            if(num < pre && (dp[i - 1][0] <= num || dp[i - 1][1] <= pre)) {
                dp[i][1] = dp[i - 1][1], info[i][1] = 1;
            } else {
                dp[i][1] = pre, info[i][1] = 0;
            }
        } else dp[i][1] = INT_MAX;
    }
    std_out();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};