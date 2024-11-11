/**
 * @Time : 2022/8/16-1:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你两个字符串 s1 和 s2 ，它们长度相等，请你检查是否存在一个 s1  的排列可以打破 s2 的一个排列，或者是否存在一个 s2 的排列可以打破 s1 的一个排列。

字符串 x 可以打破字符串 y （两者长度都为 n ）需满足对于所有 i（在 0 到 n - 1 之间）都有 x[i] >= y[i]（字典序意义下的顺序）。

 

示例 1：

输入：s1 = "abc", s2 = "xya"
输出：true
解释："ayx" 是 s2="xya" 的一个排列，"abc" 是字符串 s1="abc" 的一个排列，且 "ayx" 可以打破 "abc" 。
示例 2：

输入：s1 = "abe", s2 = "acd"
输出：false
解释：s1="abe" 的所有排列包括："abe"，"aeb"，"bae"，"bea"，"eab" 和 "eba" ，s2="acd" 的所有排列包括："acd"，"adc"，"cad"，"cda"，"dac" 和 "dca"。然而没有任何 s1 的排列可以打破 s2 的排列。也没有 s2 的排列能打破 s1 的排列。
示例 3：

输入：s1 = "leetcodee", s2 = "interview"
输出：true
 

提示：

s1.length == n
s2.length == n
1 <= n <= 10^5
所有字符串都只包含小写英文字母。


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/check-if-a-string-can-break-another-string
 */
class Solution {
public:
    /**
     * s要能打破t，那么对于t中的任意一个字符t[i]
     * 应该要找到一个s[j]最小，且能大于等于t[i]
     * 如果找的s[j]不是最小，后面遇到更大的t[i]就可能找不到s中大于等于的字母了
     *
     * 如果t中第三小的字母，需要s中第四小的字母才能打破
     * 那显然t中后续的字母至少有一个字母，在s中没法找到一个大于等于的字母去对应了
     *
     * 执行用时：68 ms, 在所有 C++ 提交中击败了59.65%的用户内存消耗：
     * 13.8 MB, 在所有 C++ 提交中击败了7.02%的用户
     */
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(), s1.end()), sort(s2.begin(), s2.end());
        return check(s1,s2) || check(s2, s1);
    }

    bool check(string s, string t){
        for(int i = 0; i < s.size(); i++)
            if(s[i] < t[i]) return false;
        return true;
    }

    /**
     * 排序，因为两个字符串都只有小写字母，所以可以使用桶排序的方式来排
     * 只不过进行进一步check的时候
     * 如果s要打破t，那么从a到z的遍历顺序中
     * s前缀和要小于等于t，否则截止到某一个字母，s多出来的，就找不到t中的字母来打败了
     *
     * 执行用时：12 ms, 在所有 C++ 提交中击败了99.12%的用户
     * 内存消耗：11.4 MB, 在所有 C++ 提交中击败了19.30%的用户
     */
    bool checkIfCanBreak2(string s1, string s2) {
        vector<int> count1 = getCount(s1), count2 = getCount(s2);
        return check(count1,count2) || check(count2, count1);
    }

    vector<int> getCount(string& s){
        vector<int> count = vector(26, 0);
        for(char c : s)
            count[c - 'a']++;
        return count;
    }

    bool check(vector<int>& count1, vector<int>& count2){
        for(int i = 0, sum1 = 0, sum2 = 0; i < 26; i++){
            sum1 += count1[i], sum2 += count2[i];
            if(sum1 > sum2) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}