/**
 * @Time : 2023/4/24-3:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 拿披萨的规则保证了
     * 1. 只能选取3n块披萨里的n块
     * 2. 相邻的两块不能选（因为是环形披萨 首尾不能同时选）
     *
     * 对于任意一种在长度为3n的环状序列上选择n个不相邻数的方法，都等价于一种题目中挑选披萨的方法
     *
     * 定义dp[i][j]表示前i个元素，挑选了j个的最大和，并且元素不能连续选取
     * 首尾不能同时选的问题：
     * 可以分情况，选到首元素时，数组中剔除尾元素；选到尾元素时，数组中剔除头元素
     */
    int maxSizeSlices(vector<int>& slices) {
        vector<int> arr1 = vector(slices.begin(), slices.end() - 1); // 选首元素，不要尾元素
        vector<int> arr2 = vector(slices.begin() + 1, slices.end());
        return max(maxSize(arr1), maxSize(arr2));
    }

    int maxSize(vector<int>& num) {
        int n = num.size(), m = (n + 1) / 3;
        vector<vector<int>> dp(n + 1, vector(m + 1, 0));
        dp[1][1] = num[0];
        for(int i = 2; i <= n; i++){
            for(int j = 1; j <= min(m, (n + 1) / 2); j++)
                dp[i][j] = max(dp[i - 1][j], dp[i - 2][j - 1] + num[i - 1]);
        }
        return dp[n][m];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}