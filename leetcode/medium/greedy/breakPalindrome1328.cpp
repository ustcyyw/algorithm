/**
 * @Time : 2022/9/2-1:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个由小写英文字母组成的回文字符串 palindrome ，请你将其中 一个 字符用任意小写英文字母替换，使得结果字符串的 字典序最小 ，且 不是 回文串。

请你返回结果字符串。如果无法做到，则返回一个 空串 。

如果两个字符串长度相同，那么字符串 a 字典序比字符串 b 小可以这样定义：在 a 和 b 出现不同的第一个位置上，字符串 a 中的字符严格小于 b 中的对应字符。例如，"abcc” 字典序比 "abcd" 小，因为不同的第一个位置是在第四个字符，显然 'c' 比 'd' 小。

 
示例 1：

输入：palindrome = "abccba"
输出："aaccba"
解释：存在多种方法可以使 "abccba" 不是回文，例如 "zbccba", "aaccba", 和 "abacba" 。
在所有方法中，"aaccba" 的字典序最小。
示例 2：

输入：palindrome = "a"
输出：""
解释：不存在替换一个字符使 "a" 变成非回文的方法，所以返回空字符串。
 

提示：

1 <= palindrome.length <= 1000
palindrome 只包含小写英文字母。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/break-a-palindrome
 */
class Solution {
public:
    /**
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：6.1 MB, 在所有 C++ 提交中击败了22.58%的用户
     */
    string breakPalindrome(string palindrome) {
        int n = palindrome.size(), m = n % 2 == 0 ? n / 2 : n / 2 + 1;
        if(n == 1) return "";
        int i = 0;
        while (i < m && palindrome[i] == 'a') i++;
        // 如果i达到m，说明整个字符串全是a；
        // 或者i指向了奇数长度的字符串的中间，两边都是a，改中间字母还是回文
        // 两种情况都要字典序最小，就只能最后一个字母改成b了，这样也能破坏回文
        if(i == m || i == m - 1 && n % 2 != 0)
            palindrome[n - 1] = 'b';
        else // 其余情况下，在非中心位置遇到了非a的字母，直接改成a就能获得字典序最小的非回文
            palindrome[i] = 'a';
        return palindrome;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}