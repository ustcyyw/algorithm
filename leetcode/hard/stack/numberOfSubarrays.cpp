/**
 * @Time : 2024/4/14-3:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛128 t4 单调栈
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 考虑枚举右边界 假设当前右边界的值为num
     * 那么其左边比 < num的数 后续也不可能再成为满足条件的子数组的左边界
     * 因为但凡左边界取num左边且<num的，那个子数组的最大值至少是num 不满足条件
     * 因此遍历过程中要将小于num的数去掉，而大于num的数是有可能成为后续满足条件的子数组的左边界
     *
     * 另外一个要考虑的问题是，num的左边还有多少个值为num的数可以成为其左边界
     * 在没有遇到>num的数时，所以出现的其它值为num的位置都可以是其左边界
     * 因此要在遍历过程中进行计数，而且结合前面考虑数的失效情况
     * 一旦num使小于它的数失效 这些数的计数就需要清0
     *
     * 从计算失效的数以及保留仍旧有效的数来看 需要使用单调栈 栈中元素单调递减
     */
    long long numberOfSubarrays(vector<int>& nums) {
        long long n = nums.size(), ans = n; // 初始答案的时候就将单个元素的子数组计算进去
        stack<int> stack;
        unordered_map<int, int> cnt; // 用于计数
        for(int num : nums) {
            while(!stack.empty() && stack.top() < num) {
                cnt[stack.top()] = 0; // 失效的数 计数就需要清0
                stack.pop();
            }
            if(!stack.empty() && stack.top() == num)
                ans += cnt[num];
            stack.push(num);
            cnt[num]++;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}