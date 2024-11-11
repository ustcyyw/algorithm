/**
 * @Time : 2023/12/10-2:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛375 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 最大元素记为maxV
     * 前缀和计算区间上的maxV的数量
     * 使用双指针 i 表示子数组的左边界。移动i的时候移动j保证区间[i,j]上有k个maxV 且j最小
     * 那么[j, n - 1]上都是都是可取的右边界
     */
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size(), maxV = 0;
        for(int num : nums)
            maxV = max(maxV, num);
        vector<int> sum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + (nums[i - 1] == maxV);
        long long res = 0;
        for(int i = 0, j = 0; i < n; i++) {
            while(j < n && sum[j + 1] - sum[i] < k) j++;
            res += n - j;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}