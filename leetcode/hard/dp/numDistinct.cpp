/**
 * @Time : 2022/7/7-8:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。

字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

题目数据保证答案符合 32 位带符号整数范围。

 

示例 1：

输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
rabbbit
rabbbit
rabbbit
示例 2：

输入：s = "babgbag", t = "bag"
输出：5
解释：
如下图所示, 有 5 种可以从 s 中得到 "bag" 的方案。
babgbag
babgbag
babgbag
babgbag
babgbag
 

提示：

0 <= s.length, t.length <= 1000
s 和 t 由英文字母组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/distinct-subsequences
 */
class Solution {
public:
    /**
     * 执行用时：4 ms, 在所有 C++ 提交中击败了99.72%的用户
     * 内存消耗：29 MB, 在所有 C++ 提交中击败了72.00%的用户
     *
     * 假如t的长度为m
     * 对于t中的字符t[m-1]
     * 子序列最后一个字母是t[m-1],那么s中每一个与t[m-1]的字母都可能是子序列的最后一个字母
     * （当然要注意字符串长度的问题，要保证其前面还有m-1个字母，那得从索引m-1开始枚举）
     * t[m-1]能有多少种可能，取决于s中的t[m-2]字母有多少种合法的可能，加和就是结果
     * 于是要去计算各个位置的t[m-2]的可能性，又要去找t[m-3]
     * 类推到找s中的t[0]
     * 在区间范围s[0, n - m]中的每一个字母t[0]，都可能是t的起点，因此值为1
     *
     * 后续就从t[1],t[2]一直计算到t[m-1]
     * 每一次计算都需要计算上一个字母的和（合理区间内的[i - 1, n - m + i]），因此要类似于前缀和一样需要数组 count 来记录
     *
     * 合理区间的计算：
     * 考虑t中的第i个字母
     * 那么其前面得有i-1个字母，因此s中对t[i]的枚举从索引i-1开始
     * 其后面还有m-i个字母，那么枚举到s中到j索引时，要保证后续还有m-i个字母，
     * 就需要 n - j >= m - i  --> j <= n - m + i
     */
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<long long> count = vector(n, 0ll);
        for(int i = 0; i <= n - m; i++)
            count[i] = s[i] == t[0] ? 1 : 0;
        for(int i = 1; i < m; i++){
            vector<long long> temp = vector(n, 0ll);
            long long sum = 0;
            // 考虑t中的第i个字母，那么其前面得有i-1个字母，因此s中对t[i]的枚举从索引i-1开始
            for(int j = i - 1; j <= n - m + i; j++){
                if(s[j] == t[i]) temp[j] = sum; // 遇到了当前计算的t中的字母，可能的数目就是前序和
                sum += count[j];
            }
            count = temp;
        }
        int res = 0;
        for(int j = n - 1; j >= m - 1; j--){
            if(s[j] == t[m - 1])
                res += count[j];
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}