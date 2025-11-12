/**
 * @Time : 2024/7/12-1:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1551E 动态规划 前后缀分解 暴力枚举
 */
 /*
  * 暴力枚举删除的位置的分界线 在分界线的左边 可以删除元素 右边一个元素都不删
  * 然后枚举分界线左边具体删了多少个元素 那么分界线右边有多少个满足条件的数就确定了
  * 左边则可以使用动态规划计算最大满足条件的数
  * dp[i][j]: 截止第i个位置 删除了j个数 最大符合个数
  * 1. 删除当前数 dp[i-1][j - 1]
  * 2. 不删当前数 dp[i-1][j] + (nums[i] == i - j)
  * dp计算出来的是前缀 后缀就是直接暴力计算即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2005, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, nums[2005], dp[N][N], suf[N][N];

int solve() {
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            dp[i][j] = dp[i-1][j] + (nums[i] == i - j);
            if(j - 1 >= 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
        }
    }
    for(int j = 0; j < n; j++) {
        for(int i = n, cnt = 0; i >= j + 1; i--) {
            if(nums[i] == i - j) cnt++;
            if(cnt + dp[i - 1][j] >= k) return j;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};