/**
 * @Time : 2022/12/8-10:10 AM
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
     * dp[i][0]表示第i个位置不进行交换满足单调增的最小交换次数
     * dp[i][1]表示第i个位置进行交换满足单调增的最小交换次数
     */
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), error_val = n + 10;
        vector<vector<int>> dp(n, vector(2, error_val));
        dp[0][0] = 0, dp[0][1] = 1;
        for(int i = 1; i < n; i++){
            // 计算当前不交换
            // 1.前一位不交换能满足递增的情况下，比较两个数组是否比前面都大
            if(dp[i - 1][0] != error_val && nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1])
                dp[i][0] = dp[i - 1][0];
            // 2.前一位交换能满足递增的情况下，比较两个数组是否比前面交叉后的大
            if(dp[i - 1][1] != error_val && nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1])
                dp[i][0] = min(dp[i][0], dp[i - 1][1]);
            // 计算当前交换的情况
            // 1.前一位不交换能满足递增的情况下，当前位交换后能满足比前一位更大
            if(dp[i - 1][0] != error_val && nums2[i] > nums1[i - 1] && nums1[i] > nums2[i - 1])
                dp[i][1] = dp[i - 1][0] + 1;
            // 2.前一位交换能满足递增的情况下，当前位交换后比交换后的前一位更大
            if(dp[i - 1][1] != error_val && nums2[i] > nums2[i - 1] && nums1[i] > nums1[i - 1])
                dp[i][1] = min(dp[i][1], dp[i - 1][1] + 1);
        }
        return min(dp[n - 1][0], dp[n - 1][1]);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}