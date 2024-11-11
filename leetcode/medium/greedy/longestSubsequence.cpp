/**
 * @Time : 2022/6/19-5:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个二进制字符串 s 和一个正整数 k 。

请你返回 s 的 最长 子序列，且该子序列对应的 二进制 数字小于等于 k 。

注意：

子序列可以有 前导 0 。
空字符串视为 0 。
子序列 是指从一个字符串中删除零个或者多个字符后，不改变顺序得到的剩余字符序列。
 

示例 1：

输入：s = "1001010", k = 5
输出：5
解释：s 中小于等于 5 的最长子序列是 "00010" ，对应的十进制数字是 2 。
注意 "00100" 和 "00101" 也是可行的最长子序列，十进制分别对应 4 和 5 。
最长子序列的长度为 5 ，所以返回 5 。
示例 2：

输入：s = "00101001", k = 1
输出：6
解释："000001" 是 s 中小于等于 1 的最长子序列，对应的十进制数字是 1 。
最长子序列的长度为 6 ，所以返回 6 。
 

提示：

1 <= s.length <= 1000
s[i] 要么是 '0' ，要么是 '1' 。
1 <= k <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/longest-binary-subsequence-less-than-or-equal-to-k
 */
class Solution {
public:
    /**
     * 贪心 1要尽可能的在低位。用低位低1去换高位的1没有意义，贡献的长度都是1
     * 用0换1也没有任何意义
     * 所以从低位开始考虑
     */
    int longestSubsequence(string s, int k) {
        int len = 0, sum = 0;
        for(int i = s.size() - 1; i >= 0; i--){
            if(s[i] == '0') len++;
            else if(len < 31 && sum + (1 << len) <= k){
                sum += (1 << len);
                len++;
            }
        }
        return len;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}