/**
 * @Time : 2023/11/27-10:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 3e3 + 5;
int n, a[N], b[N];

int solve() {
    // dp[i][j]: 用a[1,i]和b[1,j]且以 b[j]为结尾的最长公共上升子序列长度
    vector<vector<int>> dp(n + 1, vector(n + 1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1, maxv = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            if(b[j] == a[i])
                dp[i][j] = max(dp[i][j], maxv);
            if(b[j] < a[i])
                maxv = max(maxv, dp[i - 1][j] + 1);
        }
    }
    int res = 0;
    for(int j = 1; j <= n; j++)
        res = max(res, dp[n][j]);
    return res;
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];
    cout << solve() << endl;

    return 0;
}

/*
 * 最长公共上升子序列
 *
 * 在最长上升子序列中 dp[i]:以i为结尾的最长上升子序列长度
 * dp[i] = max{dp[j] + 1, if a[i] > a[j]}
 *
 * 在最长公共子序列中 dp[i][j]:以a[0,i],b[0,j]上的数字能构成的最长公共子序列长度
 * dp[i][j]:
 * if(a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 1
 * else dp[i][j] = dp[i-1][j], dp[i][j-1]
 *
 * 本问题 将以上两个基础问题结合
 * dp[i][j]: 以a[0,i],b[0,j]上的数字，且以b[j]为结尾能构成的最长公共上升子序列长度
 * 根据公共子序列的划分方式
 * 1.这个公共上升子序列不包含a[i], 那就在以a[0,i-1],b[0,j]上的数字且以b[j]为结尾的公共上升子序列中找最长
 * 问题的答案就是 dp[i-1][j]
 * 2.这个公共上升子序列包含a[i]，那么需要满足a[i] == b[j]
 *   在这个子问题下面，就需要根据上升子序列问题的思路 看一看 b[j]能接在哪些b[k]后
 *   也就是说b[j] > b[k]，且因为a[i]是与b[j]配对，因此前置序列以b[k]为结尾，并且使用了a[0,i-1]上的数字
 *   问题的答案是dp[i-1][k], 然后再加上a[i],b[j]增加的长度1
 *   dp[i][j] = max{dp[i-1][k], for b[j] > b[k]} + 1
 */
#include<bits/stdc++.h>
using namespace std;
// n ^ 3的时间复杂度 但是可以进行优化
int solve1(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size();
    vector<vector<int>> dp(n + 1, vector(n + 1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            if(arr1[i - 1] == arr2[j - 1]) {
                dp[i][j] = max(1, dp[i][j]); // 不能忘记由当前两个相等数字构成的长度为1的集合
                for(int k = 1; k < j; k++) {
                    if(arr2[j - 1] > arr2[k - 1])
                        dp[i][j] = max(dp[i][j], dp[i - 1][k] + 1);
                }
            }
        }
    }
    int res = 0;
    for(int j = 1; j <= n; j++)
        res = max(res, dp[n][j]);
    return res;
}
/*
 * 前缀优化 先写对思路 保持代码结构不变的情况下，再进行优化
 * 注意 第二层循环中的 if的逻辑分枝中 arr1[i - 1] == arr2[j - 1]
 * 于是可以将第三层循环中的 if(arr2[j - 1] > arr2[k - 1])
 * 等价替换为 if(arr1[i - 1] > arr2[k - 1])
 *
 * 于是第三层循环
 * for(int k = 1; k < j; k++)
 *     if(arr1[i - 1] > arr2[k - 1])
 * 除了循环范围与j有关 找的最大值 max_v = max{dp[i - 1][k] + 1} 以及if条件都与j无关
 * 那么在二层循环j的时候 就能将这件事顺带完成
 * 只需要在更新dp[i][j]后再更新max_v 就能保证更新dp[i][j]时，k实际上只取到j-1 满足k < j
 * 将第三层循环优化掉了
 */
int solve2(vector<int>& arr1, vector<int>& arr2) {
    int n = arr1.size();
    vector<vector<int>> dp(n + 1, vector(n + 1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1, max_v = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            if(arr1[i - 1] == arr2[j - 1])
                dp[i][j] = max(dp[i][j], max_v);
            if(arr1[i - 1] > arr2[j - 1])
                max_v = max(max_v, dp[i - 1][j] + 1);
        }
    }
    int res = 0;
    for(int j = 1; j <= n; j++)
        res = max(res, dp[n][j]);
    return res;
}