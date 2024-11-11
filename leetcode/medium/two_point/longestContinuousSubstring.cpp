/**
 * @Time : 2022/9/18-2:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 字母序连续字符串 是由字母表中连续字母组成的字符串。换句话说，字符串 "abcdefghijklmnopqrstuvwxyz" 的任意子字符串都是 字母序连续字符串 。

例如，"abc" 是一个字母序连续字符串，而 "acb" 和 "za" 不是。
给你一个仅由小写英文字母组成的字符串 s ，返回其 最长 的 字母序连续子字符串 的长度。

 

示例 1：

输入：s = "abacaba"
输出：2
解释：共有 4 个不同的字母序连续子字符串 "a"、"b"、"c" 和 "ab" 。
"ab" 是最长的字母序连续子字符串。
示例 2：

输入：s = "abcde"
输出：5
解释："abcde" 是最长的字母序连续子字符串。
 

提示：

1 <= s.length <= 105
s 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/length-of-the-longest-alphabetical-continuous-substring
 */
class Solution {
public:
    int longestContinuousSubstring(string s) {
        int res = 1, n = s.size();
        for(int i = 0, j = 1; i < n; j++){
            while (j < n && s[j] == s[i] + 1) j++;
            res = max(res, j - i);
            i = j;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}