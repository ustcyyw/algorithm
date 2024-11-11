/**
 * @Time : 2022/6/17-1:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 如果一个二进制字符串，是以一些 0（可能没有 0）后面跟着一些 1（也可能没有 1）的形式组成的，那么该字符串是 单调递增 的。

给你一个二进制字符串 s，你可以将任何 0 翻转为 1 或者将 1 翻转为 0 。

返回使 s 单调递增的最小翻转次数。

 

示例 1：

输入：s = "00110"
输出：1
解释：翻转最后一位得到 00111.
示例 2：

输入：s = "010110"
输出：2
解释：翻转得到 011111，或者是 000111。
示例 3：

输入：s = "00011000"
输出：2
解释：翻转得到 00000000。
 

提示：

1 <= s.length <= 105
s[i] 为 '0' 或 '1'

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/flip-string-to-monotone-increasing
 */
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        vector<int> sum = vector(n + 1, 0);
        for(int i = 0; i < n; i++)
            sum[i + 1] += sum[i] + (s[i] - '0');
        int res = min(n - sum[n], sum[n]);
        for(int i = 0; i < n; i++)
            // sum[i + 1] : 区间[0, i]上的1
            // n - i - 1 区间[i + 1, n - 1]上的元素个数
            // sum[n] - sum[i + 1]: 区间[i + 1, n - 1]上的1的个数
            res = min(res, sum[i + 1] + n - i - 1 - (sum[n] - sum[i + 1]));
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}