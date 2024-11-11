/**
 * @Time : 2023/4/19-9:06 PM
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
     * 开始会想到 找到target和arr的最长公共子序列 （lcs）
     * 然后在最长公共子序列的基础上，向arr中插入元素 就可以最少得使target变为arr的子序列
     * 但是lcs问题的时间复杂度是n*m的 直接这样做 会超时
     *
     * 但是注意 target中的元素是唯一的 这意味着
     * 任何一个公共子序列，在target对应的下标 都是递增的
     * 也就是说最长公共子序列lcs就是 target中对应下标递增的最长子序列
     * 问题转化 求最长上升子序列lis，只不过这里子序列中元素的大小关系以target中该元素的下标去定义
     */
    int minOperations(vector<int>& target, vector<int>& arr) {
        unordered_map<int, int> map;
        for(int i = 0; i < target.size(); i++)
            map[target[i]] = i;
        vector<int> nums;
        for(int num : arr){ // 不在target中的元素无影响，在target中的元素按其在target中的下标排列
            if(map.count(num))
                nums.push_back(map[num]);
        }
        // 求lis 经典的单调优化dp 定义dp[i]表示子序列长度为i+1时，第i个元素的最小值
        if(nums.empty()) return (int)target.size();
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        int len = 1;
        for(int i = 1; i < nums.size(); i++) {
            int num = nums[i], lo = 0, hi = len;
            while (lo < hi) { // 二分找到num该插入的位置
                int mid = (lo + hi) >> 1;
                if(dp[mid] < num) lo = mid + 1;
                else hi = mid;
            }
            if(lo == len) len++;
            dp[lo] = num;
        }
        return (int)target.size() - len;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}