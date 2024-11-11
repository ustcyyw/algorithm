/**
 * @Time : 2023/10/28-4:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给定一个 下标从0开始 的整数数组 nums，以及两个整数 x 和 y。在每一次操作中，你需要选择一个满足条件 0 <= i < nums.length 的下标 i ，并执行以下操作：

将 nums[i] 减去 x。
将除了下标为 i 的位置外，其他位置的值都减去 y。
返回使得 nums 中的所有整数都 小于等于零 所需的最小操作次数。



示例 1：

输入：nums = [3,4,1,7,6], x = 4, y = 2
输出：3
解释：你需要进行三次操作。其中一种最优操作序列如下：
操作 1: 选择 i = 3。 然后, nums = [1,2,-1,3,4].
操作 2: 选择 i = 3。 然后, nums = [-1,0,-3,-1,2].
操作 3: 选择 i = 4。 然后, nums = [-3,-2,-5,-3,-2].
现在，nums 中的所有数字都是非正数。因此，返回 3。
示例 2：

输入：nums = [1,2,1], x = 2, y = 1
输出：1
解释：我们可以在 i = 1 处执行一次操作，得到 nums = [0,0,0]。所有正数都被移除，因此返回 1。


提示：

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= y < x <= 109
 */
class Solution {
public:
    long long x, y;
    int minOperations(vector<int>& nums, int x, int y) {
        this->x = x, this->y = y;
        int lo = 1, hi = 1e9;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(nums, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(vector<int>& nums, int cnt) {
        int cx = cnt;
        for(int num : nums) {
            if(y * cnt >= num) continue;
            if(x * cnt < num) return false;
            cx -= min_x(num, cnt);
            if(cx < 0) return false;
        }
        return true;
    }

    int min_x(int num, int cnt) {
        int lo = 0, hi = cnt;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(x * mid + y * (cnt - mid) >= num) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}