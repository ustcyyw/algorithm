/**
 * @Time : 2022/7/7-6:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给定一个字符串 s，请将 s 分割成一些子串，使每个子串都是回文串。

返回符合要求的 最少分割次数 。

 

示例 1：

输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
示例 2：

输入：s = "a"
输出：0
示例 3：

输入：s = "ab"
输出：1
 

提示：

1 <= s.length <= 2000
s 仅由小写英文字母组成
 

注意：本题与主站 132 题相同： https://algorithm-cn.com/problems/palindrome-partitioning-ii/



来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/omKAoA
 */
class Solution {
public:
    /**
     * 执行用时：28 ms, 在所有 C++ 提交中击败了89.41%的用户
     * 内存消耗：7.8 MB, 在所有 C++ 提交中击败了84.22%的用户
     *
     * dp[i]表示 [0, i]上的字符串最少需要切割多少次全变为回文子串
     * 不像常规的区间dp，这里没有三层枚举
     * 这是因为可以固定右端为单一子串，这是因为
     * 假定现在枚举区间 [a,b]，切割点为k， 分为[a,k],[k + 1, b]
     * 如果[k + 1, b]不是一个回文串，还能再找一个切割点l分为[k + 1, l],[l + 1, b]
     * 其中[l + 1, b]为一个回文串，于是[k + 1, b]上的切割次数就变为 [k + 1, l] + 1
     * 整体就变为 [a,k] + [k + 1, l] + 1，如果分开考虑[a,k]和[k + 1, l]的最小切割数再相加
     * 一定不如[a,l]整体考虑，因为前者是后者的一个子集。
     * 因此[a,b]的枚举就变为 min{[a,l]} + 1,其中l使得[l + 1, b]为一个回文串
     */
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> check = vector(n, vector(n, false));
        for(int i = 0; i < n; i++){
            for(int lo = i, hi = i; lo >= 0 && hi < n && s[lo] == s[hi]; hi++, lo--)
                check[lo][hi] = true;
            for(int lo = i, hi = i + 1; lo >= 0 && hi < n && s[lo] == s[hi]; hi++, lo--)
                check[lo][hi] = true;
        }
        vector<int> dp = vector(n, 2001); // [0, i]上的字符串最少需要切割多少次全变为回文子串
        for(int i = 0; i < n; i++){
            if(check[0][i]) {
                dp[i] = 0;
                continue;
            }
            for(int j = 0; j < i; j++){
                if(check[j + 1][i])
                    dp[i] = min(dp[i], 1 + dp[j]);
            }
        }
        return dp[n - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}