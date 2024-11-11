/**
 * @Time : 2022/7/28-12:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的二进制字符串 s 和两个整数 minJump 和 maxJump 。一开始，你在下标 0 处，且该位置的值一定为 '0' 。当同时满足如下条件时，你可以从下标 i 移动到下标 j 处：

i + minJump <= j <= min(i + maxJump, s.length - 1) 且
s[j] == '0'.
如果你可以到达 s 的下标 s.length - 1 处，请你返回 true ，否则返回 false 。

 

示例 1：

输入：s = "011010", minJump = 2, maxJump = 3
输出：true
解释：
第一步，从下标 0 移动到下标 3 。
第二步，从下标 3 移动到下标 5 。
示例 2：

输入：s = "01101110", minJump = 2, maxJump = 3
输出：false
 

提示：

2 <= s.length <= 105
s[i] 要么是 '0' ，要么是 '1'
s[0] == '0'
1 <= minJump <= maxJump < s.length

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/jump-game-vii
 */
class Solution {
public:
    /**
     * 执行用时：36 ms, 在所有 C++ 提交中击败了90.16%的用户
     * 内存消耗：18.3 MB, 在所有 C++ 提交中击败了59.84%的用户
     */
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        if(s[n - 1] == '1') return false;
        queue<int> queue;
        queue.push(0);
        int r = 0;
        while (!queue.empty()){
            int cur = queue.front();
            if(cur + minJump > n - 1) return false; // 最左边的0 都一定会跳超过终点，所以不可能到达
            if(cur + maxJump >= n - 1) return true; // 在不会跳超过终点的情况下，该点可以到达终点，直接返回true
            for(int i = max(cur + minJump, r); i <= cur + maxJump; i++)
                if(s[i] == '0') queue.push(i);
            r = cur + maxJump + 1; // r-1表示已经扫描过是否有0的区域
            queue.pop();
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}