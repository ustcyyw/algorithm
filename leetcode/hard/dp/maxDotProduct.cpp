/**
 * @Time : 2022/8/17-10:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 本题可以与最长公共字符序列类比
     *
     * dp[i][j]: nums1[0,i], nums2[0,j]上的最大点乘
     * 边界条件dp[0][j]：使用nums1[0]与nums2[0,j]中一个数相乘的最大值
     * dp[i][0]，类似的
     *
     * dp[i][j]:
     * 1.不使用nums1[i]，则保留dp[i - 1][j]的结果
     * 2.不用nums2[j]，则保留dp[i][j - 1]的结果
     * 3.同时使用nums1[i]，nums2[j], dp[i-1][j-1] + nums2[j] * nums1[i]
     * 当前两个元素点乘加上前置结果
     *
     * 乍一看似乎是常规的dp写法，但是要注意本题中的数字可以是负数
     * dp[k-1][j-1]这一项可能是负的(要求了非空)
     * nums1[i] * nums2[j]这一项已经保证了dp[i][j]非空
     * 如果dp[i-1][j-1] < 0这一项是拖累，就不应该取
     * 所以情况3正确的方程应中的dp[i-1][j-1]是
     * dp[i-1][j-1] > 0 ? dp[i-1][j-1] : 0 等价于 max(0, dp[i-1][j-1])
     *
     * 执行用时：20 ms, 在所有 C++ 提交中击败了79.05%的用户
     * 内存消耗：12.7 MB, 在所有 C++ 提交中击败了59.05%的用户
     */
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<vector<int>> dp = vector(n, vector(m, -1000000000));
        dp[0][0] = nums1[0] * nums2[0];
        for(int i = 1; i < n; i++)
            dp[i][0] = max(dp[i - 1][0], nums1[i] * nums2[0]);
        for(int j = 1; j < m; j++)
            dp[0][j] = max(dp[0][j - 1], nums1[0] * nums2[j]);
        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                int temp = max(dp[i][j - 1], dp[i - 1][j]);
                dp[i][j] = max(temp, nums1[i] * nums2[j] + max(0, dp[i - 1][j - 1]));
            }
        }
        return dp[n - 1][m - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}