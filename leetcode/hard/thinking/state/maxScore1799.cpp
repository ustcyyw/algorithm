/**
 * @Time : 2022/10/14-10:43 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你 nums ，它是一个大小为 2 * n 的正整数数组。你必须对这个数组执行 n 次操作。

在第 i 次操作时（操作编号从 1 开始），你需要：

选择两个元素 x 和 y 。
获得分数 i * gcd(x, y) 。
将 x 和 y 从 nums 中删除。
请你返回 n 次操作后你能获得的分数和最大为多少。

函数 gcd(x, y) 是 x 和 y 的最大公约数。

 

示例 1：

输入：nums = [1,2]
输出：1
解释：最优操作是：
(1 * gcd(1, 2)) = 1
示例 2：

输入：nums = [3,4,6,8]
输出：11
解释：最优操作是：
(1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11
示例 3：

输入：nums = [1,2,3,4,5,6]
输出：14
解释：最优操作是：
(1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14
 

提示：

1 <= n <= 7
nums.length == 2 * n
1 <= nums[i] <= 106

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximize-score-after-n-operations
 */
class Solution {
public:
    /**
     * 执行用时：76 ms, 在所有 C++ 提交中击败了81.48%的用户
     * 内存消耗：17.8 MB, 在所有 C++ 提交中击败了20.00%的用户
     */
    int n;
    vector<vector<int>> vals, cache;
    int maxScore(vector<int>& nums) {
        n = nums.size();
        vals = vector(n, vector(n, 0));
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++)
                vals[i][j] = gcd(nums[i], nums[j]);
        }
        cache = vector(n / 2 + 1, vector(1 << n, 0));
        return max_score(1, (1 << n) - 1);
    }

    int max_score(int i, int state){
        if(state == 0) return 0;
        if(cache[i][state]) return cache[i][state];
        int res = 0;
        for(int j = 0; j < n; j++){
            if(((1 << j) & state) == 0) continue;
            for(int k = j + 1; k < n; k++){
                if(((1 << k) & state) == 0) continue;
                int ns = state ^ (1 << k) ^ (1 << j);
                res = max(res, i * vals[j][k] + max_score(i + 1, ns));
            }
        }
        cache[i][state] = res;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}