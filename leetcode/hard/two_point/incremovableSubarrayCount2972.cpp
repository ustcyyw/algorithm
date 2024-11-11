/**
 * @Time : 2023/12/26-4:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛120 t3
 */

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 注意是子数组
     * 分两类情况讨论：
     * 1.删除某个前缀 让剩余的序列递增
     * 那就要先找到最长递增后缀，假设最长后缀是nums[j, n - 1]
     * 令t = max(j - 1, 0)，那么nums[0,t], nums[0, t + 1], nums[0, n - 1]被删除后 剩余序列是递增的
     * 一共有 n - t 种删除方法
     *
     * 2.删除中间的子数组 让头尾剩余的序列合在一起也递增
     * 删除的子数组如果是nums[i + 1,j]
     * 需要同时满足三个条件
     * a.前缀是递增的，b.后缀也是递增的，c.并且nums[i] < nums[j + 1]
     * 对于条件b，已经在情况1中讨论了最长递增后缀，j一定在该范围内
     * 对于条件a 枚举i的同时就能判断
     * 对于条件c 由于前缀是递增的 后缀也是递增的 所以i向右移动的时候 j也会同向移动（双指针）
     * 找到满足条件的最小的j，可选的删除方案 右边界就是 [j-1,n-1] 这个范围
     * 但是子数组nums[i+1,j]存在，则需要满足j >= i + 1，因此可以删除的右边界范围是[max(j-1,i+1), n - 1]
     * 一共有 n - max(j-1,i+1) 种方法
     */
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size(), j = n - 1;
        while(j > 0 && nums[j - 1] < nums[j]) j--;
        long long res = n - max(j - 1, 0);
        for(int i = 0; i < n; i++) {
            if(i > 0 && nums[i - 1] >= nums[i])
                break;
            while(j < n && nums[j] <= nums[i]) j++;
            res += n - max(j - 1, i + 1);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}