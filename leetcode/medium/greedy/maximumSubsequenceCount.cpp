/**
 * @Time : 2022/8/10-5:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的字符串 text 和另一个下标从 0 开始且长度为 2 的字符串 pattern ，两者都只包含小写英文字母。

你可以在 text 中任意位置插入 一个 字符，这个插入的字符必须是 pattern[0] 或者 pattern[1] 。注意，这个字符可以插入在 text 开头或者结尾的位置。

请你返回插入一个字符后，text 中最多包含多少个等于 pattern 的 子序列 。

子序列 指的是将一个字符串删除若干个字符后（也可以不删除），剩余字符保持原本顺序得到的字符串。

 

示例 1：

输入：text = "abdcdbc", pattern = "ac"
输出：4
解释：
如果我们在 text[1] 和 text[2] 之间添加 pattern[0] = 'a' ，那么我们得到 "abadcdbc" 。那么 "ac" 作为子序列出现 4 次。
其他得到 4 个 "ac" 子序列的方案还有 "aabdcdbc" 和 "abdacdbc" 。
但是，"abdcadbc" ，"abdccdbc" 和 "abdcdbcc" 这些字符串虽然是可行的插入方案，但是只出现了 3 次 "ac" 子序列，所以不是最优解。
可以证明插入一个字符后，无法得到超过 4 个 "ac" 子序列。
示例 2：

输入：text = "aabb", pattern = "ab"
输出：6
解释：
可以得到 6 个 "ab" 子序列的部分方案为 "aaabb" ，"aaabb" 和 "aabbb" 。
 

提示：

1 <= text.length <= 105
pattern.length == 2
text 和 pattern 都只包含小写英文字母。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximize-number-of-subsequences-in-a-string
 */
class Solution {
public:
    /**
     * 执行用时：44 ms, 在所有 C++ 提交中击败了58.97%的用户
     * 内存消耗：24.3 MB, 在所有 C++ 提交中击败了22.57%的用户
     *
     * 贪心 由于pattern只有两个字母，所以最优的情况一定是第一个字母添加到最前面
     * 或者第二个字母添加到最后面
     */
    long long maximumSubsequenceCount(string text, string pattern) {
        char a = pattern[0], b = pattern[1];
        return max(count(a + text, a, b), count(text + b, a, b));
    }

    long long count(string text, char a, char b){
        long long res = 0;
        int countA = 0;
        for(char c : text){
            if(c == b) res += countA; // 在a和b相等的情况下，先统计前面出现的次数，不会出现单一字母被计数的情况
            if(c == a) countA++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}