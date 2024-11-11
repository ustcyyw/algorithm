/**
 * @Time : 2023/2/28-6:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给定由 n 个小写字母字符串组成的数组 strs ，其中每个字符串长度相等。

选取一个删除索引序列，对于 strs 中的每个字符串，删除对应每个索引处的字符。

比如，有 strs = ["abcdef","uvwxyz"] ，删除索引序列 {0, 2, 3} ，删除后为 ["bef", "vyz"] 。

假设，我们选择了一组删除索引 answer ，那么在执行删除操作之后，最终得到的数组的行中的 每个元素 都是按字典序排列的（即 (strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]) 和 (strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1]) ，依此类推）。

请返回 answer.length 的最小可能值 。

 

示例 1：

输入：strs = ["babca","bbazb"]
输出：3
解释：
删除 0、1 和 4 这三列后，最终得到的数组是 A = ["bc", "az"]。
这两行是分别按字典序排列的（即，A[0][0] <= A[0][1] 且 A[1][0] <= A[1][1]）。
注意，A[0] > A[1] —— 数组 A 不一定是按字典序排列的。
示例 2：

输入：strs = ["edcba"]
输出：4
解释：如果删除的列少于 4 列，则剩下的行都不会按字典序排列。
示例 3：

输入：strs = ["ghi","def","abc"]
输出：0
解释：所有行都已按字典序排列。
 

提示：

n == strs.length
1 <= n <= 100
1 <= strs[i].length <= 100
strs[i] 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/delete-columns-to-make-sorted-iii
 */
class Solution {
public:
    /*
     * 同时删除一列上的所有字母
     * 如果要保留当前列j，那么再往前要保留的列i，一定要满足对于所有再strs中的字符串
     * 都有str[i] <= str[j]
     * 满足这个条件就能保留j，并且将这一列接到i的后面
     * 那么保留j的最长序列长度，就可能是i做为最后一列的最长长度+1
     *
     * 问题就变成了最长上升子序列的长度了
     */
    int minDeletionSize(vector<string>& strs) {
        int n = strs[0].size(), res = n - 1;
        vector<int> dp(n, 1);
        for(int j = 1; j < n; j++){
            for(int i = 0; i < j; i++){
                if(check(strs, i, j))
                    dp[j] = max(dp[i] + 1, dp[j]);
            }
            res = min(res, n - dp[j]);
        }
        return res;
    }

    bool check(vector<string>& strs, int i, int j){
        for(string& str : strs)
            if(str[i] > str[j]) return false;
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}