/**
 * @Time : 2022/9/1-12:35 AM
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
     * 比较容易想到区间上的dp，枚举某个区间上要下一个要戳破的气球
     * 但是下一个戳破k后dp[i][k-1], dp[k+1][j]并不是独立的，因为此时k-1, k+1这两个气球会接到一块
     * 这两个区间并不能独立计算
     *
     * 而dp有一个必要的条件就是，子问题独立
     * 因此这样定义状态并不对
     *
     * 假设某一轮中，戳破了位置为k的气球
     * 并不知道其后面，前面还没破的第一个气球是谁，假定分别是nums[i]i, nums[i]j
     * 那么戳破k的分数就是 nums[i] * nums[k] * nums[j]
     * 这个时候 这一排气球的就如同 还没有破的气球切割成的多个区间
     * ..nums[2]...nums[i]....nums[k]..nums[j]...nums[n-3]..
     *
     * 定义dp[i][j]表示戳破(i,j)上所有气球的最大得分
     * 如果在区间(i,j)上最后戳破的气球是k，最后这一次得分nums[i] * nums[k] * nums[j]
     * 并且要最后戳破k，说明需要先戳破(i,k)和(k,j)上的所有气球
     * 可以看到子区间并没有受到气球k被戳破的影响
     * dp[i][j] = max{dp[i,k] + dp[k,j] + nums[i] * nums[k] * nums[j]};
     *
     * 根据状态定义，答案并不是dp[0][nums.size() - 1]，因此这个状态第一个气球和最后一个气球还在
     * 但题目中说了，如果涉及边界，就当是一个值为1的气球
     * 可以在nums的前后各加入一个值为1的气球，成为数组aux
     * 然后求这个数组的dp[0][aux.size() - 1]，就是将原数组所有气球戳破的最大分值
     *
     * 执行用时：476 ms, 在所有 C++ 提交中击败了25.89%的用户
     * 内存消耗：10.2 MB, 在所有 C++ 提交中击败了9.98%的用户
     */
    vector<vector<int>> cache;
    int maxCoins(vector<int>& nums) {
        vector<int> aux;
        aux.push_back(1);
        for(int num : nums) aux.push_back(num);
        aux.push_back(1);
        int n = aux.size();
        cache = vector(n, vector(n, - 1));
        return max_coin(aux, 0, n - 1);
    }

    int max_coin(vector<int>& nums, int lo, int hi){
        if(lo + 1 >= hi) return 0; // 此时区间(lo,hi)中没有任何元素，无法戳破气球，得分就是0
        if(cache[lo][hi] != -1) return cache[lo][hi];
        int res = 0;
        for(int k = lo + 1; k <= hi - 1; k++){ // (lo, hi)上能戳破的气球为[lo + 1, hi - 1]
            int temp = nums[lo] * nums[k] * nums[hi] + max_coin(nums, lo, k) + max_coin(nums, k, hi);
            res = max(res, temp);
        }
        cache[lo][hi] = res;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}