/**
 * @Time : 2022/7/21-10:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 字符串的 波动 定义为子字符串中出现次数 最多 的字符次数与出现次数 最少 的字符次数之差。

给你一个字符串 s ，它只包含小写英文字母。请你返回 s 里所有 子字符串的 最大波动 值。

子字符串 是一个字符串的一段连续字符序列。

 

示例 1：

输入：s = "aababbb"
输出：3
解释：
所有可能的波动值和它们对应的子字符串如以下所示：
- 波动值为 0 的子字符串："a" ，"aa" ，"ab" ，"abab" ，"aababb" ，"ba" ，"b" ，"bb" 和 "bbb" 。
- 波动值为 1 的子字符串："aab" ，"aba" ，"abb" ，"aabab" ，"ababb" ，"aababbb" 和 "bab" 。
- 波动值为 2 的子字符串："aaba" ，"ababbb" ，"abbb" 和 "babb" 。
- 波动值为 3 的子字符串 "babbb" 。
所以，最大可能波动值为 3 。
示例 2：

输入：s = "abcde"
输出：0
解释：
s 中没有字母出现超过 1 次，所以 s 中每个子字符串的波动值都是 0 。
 

提示：

1 <= s.length <= 104
s  只包含小写英文字母。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/substring-with-largest-variance
 */
class Solution {
public:
    /**
     * 关键1：想到了对最多和最少的字母进行枚举（因为都是小写字母，参考数据量发现时间是可以通过的）
     * 关键2：确定了最多的字母a和最少的字母b，一个a可以让差值+1，一个b则-1。因此想到转换为数字之后求最大子数组和
     * 关键3：本题的子串中既要有a也要有b，那就不能像53题一样直接做。
     *      类似的可以用diffWithB来表示含有b的最大差值
     *      用diff表示最大差值，使用贪心的策略更新diff
     *      在遇到b的时候，显然diff-1，并且此时一定是遇到了b，将diffWithB更新为diff
     */
    int largestVariance(string s) {
        unordered_map<char, int> first;
        for(int i = 0; i < s.size(); i++){
            if(first.find(s[i]) == first.end())
                first[s[i]] = i;
        }
        int res = 0;
        for(int i = 0; i < 26; i++){
            char a = (char)(i + 'a');
            if(first.find(a) == first.end()) continue;
            for(int j = 0; j < 26; j++){
                char b = (char)(j + 'a');
                if(i == j || first.find(b) == first.end()) continue;
                res = max(res, max_diff(s, a, b, first[a], first[b]));
            }
        }
        return res;
    }
    // 求以a为最高频元素，b为最低频元素时，子串的频数差
    int max_diff(string s, char a, char b, int startA, int startB){
        int res = 0, diff = 0, diffWithB = -100001; // 一开始没有遇到b 因此含有b的差值设置为负无穷
        for(int i = min(startB, startA); i < s.size(); i++){
            if(s[i] == a) {
                diff++;
                diffWithB++;
            }
            if(s[i] == b){
                diff--;
                diffWithB = diff; // 遇到了b，因此含有b的差值变化
            }
            if(diff < 0) diff = 0; // 53题一致的贪心，如果a比b还少了，重新找子串的开头
            res = max(res, diffWithB);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}