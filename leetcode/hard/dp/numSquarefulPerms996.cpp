/**
 * @Time : 2022/10/17-4:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个非负整数数组 A，如果该数组每对相邻元素之和是一个完全平方数，则称这一数组为正方形数组。

返回 A 的正方形排列的数目。两个排列 A1 和 A2 不同的充要条件是存在某个索引 i，使得 A1[i] != A2[i]。

 

示例 1：

输入：[1,17,8]
输出：2
解释：
[1,8,17] 和 [17,8,1] 都是有效的排列。
示例 2：

输入：[2,2,2]
输出：1
 

提示：

1 <= A.length <= 12
0 <= A[i] <= 1e9

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/number-of-squareful-arrays
 */
class Solution {
public:
    /**
     * 状态压缩的记忆化搜索
     * cache[i][status]表示可选状态为status时，选择了nums[i]，能够得到的满足题意的数量
     * 当status = 0时，所有元素都选择完毕，得到一个满足题意的组合，返回1
     * 注意去重，同一个位置的元素（status中1的个数和放置的位置也是一一映射的），值相同的只能选一次
     */
    int n;
    vector<vector<int>> cache;
    int numSquarefulPerms(vector<int>& nums) {
        n = nums.size();
        int status = (1 << n) - 1, res = 0;
        cache = vector(n, vector(status + 1, -1));
        unordered_set<int> set;
        for(int i = 0; i < n; i++){
            if(set.count(nums[i])) continue;
            set.insert(nums[i]);
            res += count(nums, i, status);
        }
        return res;
    }

    int count(vector<int>& nums, int i, int status){
        status ^= 1 << i; // i 这个元素已经被取走
        if(status == 0) return 1;
        if(cache[i][status] != -1) return cache[i][status];
        int res = 0;
        unordered_set<int> set;
        for(int j = 0; j < n; j++){
            int t = 1 << j;
            if((t & status) == 0 || set.count(nums[j])) continue;
            int sum = nums[i] + nums[j], num = (int) sqrt(sum);
            if(num * num == sum) {
                set.insert(nums[j]);
                res += count(nums, j, status);
            }
        }
        cache[i][status] = res;
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,17,8};
    s.numSquarefulPerms(arr);
    cout << 0 << endl;
}