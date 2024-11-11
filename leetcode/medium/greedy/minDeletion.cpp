/**
 * @Time : 2022/7/12-8:44 PM
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
     * 如果出现了某对 i % 2 == 0 且 nums[i] == nums[i + 1]
     * 要么删除i之前的一个数字使这两个不合规的数字前移，使条件i % 2 == 0失效
     * 要么删除这nums[i]、nums[i + 1]两个中的一个，使i和i+1的数字变化一个
     *
     * 这两种删法对后续数字的影响一致，整体前移动，这个角度是等价的
     *
     * 删除这nums[i]、nums[i + 1]两个中的一个，递补过来的数字不同了，那么二者效果一致；
     * 如果递补过来的数字还是相同，这两个位置还得删除一次
     * 从这个角度来看，也是等价的。
     *
     * 因此可以贪心地遇到不同就删除当前单词，在删除后继续向后检查
     */
    int minDeletion(vector<int>& nums) {
        int n = nums.size(), res = 0;
        if(n == 0 || n == 1) return n;
        // curIndex表示当前检查的真实位置的下标（因为数组在不停变动）
        // i是该数在原始数组中的索引，j是下一个没被删的数在原始数组中的索引，现在nums[i],nums[j]在新数组中相邻
        for(int i = 0, j = 1, curIndex = 0; j < nums.size(); j++){
            if(curIndex % 2 != 0 || nums[i] != nums[j]){ // 不需要删除，i指向下一个位置j，j也向后找下一个数j++
                i = j;
                curIndex++;
            } else { // 要删除其中一个数，就是j后移一位，i停留接着进行验证，那么curIndex也保持不变
                res++;
                n--; // 真实数组中的元素个数要-1
            }
        }
        return n % 2 == 0 ? res : res + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}