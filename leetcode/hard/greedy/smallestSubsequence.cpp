/**
 * @Time : 2022/9/1-1:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个字符串 s ，一个整数 k ，一个字母 letter 以及另一个整数 repetition 。

返回 s 中长度为 k 且 字典序最小 的子序列，该子序列同时应满足字母 letter 出现 至少 repetition 次。生成的测试用例满足 letter 在 s 中出现 至少 repetition 次。

子序列 是由原字符串删除一些（或不删除）字符且不改变剩余字符顺序得到的剩余字符串。

字符串 a 字典序比字符串 b 小的定义为：在 a 和 b 出现不同字符的第一个位置上，字符串 a 的字符在字母表中的顺序早于字符串 b 的字符。

 

示例 1：

输入：s = "leet", k = 3, letter = "e", repetition = 1
输出："eet"
解释：存在 4 个长度为 3 ，且满足字母 'e' 出现至少 1 次的子序列：
- "lee"（"leet"）
- "let"（"leet"）
- "let"（"leet"）
- "eet"（"leet"）
其中字典序最小的子序列是 "eet" 。
示例 2：



输入：s = "algorithm", k = 4, letter = "e", repetition = 2
输出："ecde"
解释："ecde" 是长度为 4 且满足字母 "e" 出现至少 2 次的字典序最小的子序列。
示例 3：

输入：s = "bb", k = 2, letter = "b", repetition = 2
输出："bb"
解释："bb" 是唯一一个长度为 2 且满足字母 "b" 出现至少 2 次的子序列。
 

提示：

1 <= repetition <= k <= s.length <= 5 * 104
s 由小写英文字母组成
letter 是一个小写英文字母，在 s 中至少出现 repetition 次

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter
 */
class Solution {
public:
    /**
     * 贪心 字典序最小
     * 就要在满足要求的情况下，让最小的字母出现在最前面
     * 比如前面已经有 bbcd 这样的序列，出现了一个a，如果将前面的四个字母都删除还能满足题意
     * 那么最小的序列应该是a开头的（bbcd都删除）
     * 这个删除的的过程类似于单调栈（字典序最小，就是单调增的，允许相等的栈）
     *
     * 本题中要满足的要求明显有两个
     * 序列长度为k和指定字母letter出现的次数大于等于repetition
     * 条件1：当前的序列长度 + 包括此字母在内的后续字母数量 >= k
     * 也就是说只有在res.size() + n - i > k的情况下才有删除字母的空间
     * 条件2：用used表示使用了多少个letter，remain[i]表示区间[i, n - 1]上还剩的指定元素个数
     * 要保证使用的letter + 当前位置之后还剩的letter >= repetition
     * 也就是说如果要被弹出的元素是letter，且used + remain[i] == repetition，这个时候不允许弹出
     */
    string smallestSubsequence(string s, int k, char letter, int repetition) {
        int n = s.size();
        vector<int> remain = vector(n, 0); // remain[i]表示区间[i, n - 1]上还剩的指定元素个数
        for(int i = n - 1, count = 0; i >= 0; i--){
            if(s[i] == letter) count++;
            remain[i] = count;
        }
        string res;
        for(int i = 0, used = 0; i < n; i++){ // used 表示使用了多少个letter
            char c = s[i];
            while (!res.empty() && res.back() > c && res.size() + n - i > k){
                if(res.back() == letter){
                    // 已经使用的letter加上还剩的刚好等于要求的最低值，如果再把letter弹出，就达不到重复次数要求了
                    if(used + remain[i] == repetition) break;
                    else {
                        used--;
                        res.pop_back();
                    }
                }
                else res.pop_back();
            }
            res.push_back(c);
            if(c == letter) used++;
        }
        if(res.size() == k) return res;
        // 循环结束之后是一个字母递增，且有大于等于repetition个letter的字符串，总长度超过k
        return modify(res, k, letter, repetition);
    }

    string modify(string& s, int k, char letter, int repetition){
        string res;
        for(int i = 0, used = 0; i < s.size() && res.size() < k; i++){
            // 字符等于letter，按字典序最小应该在这个位置，或者必须要添加才能满足repetition
            if(s[i] == letter) {
                res.push_back(letter);
                used++;
            }
            // 如果不是letter，是其它普通字符，如果剩余的位置 k - (int)res.size() 多于还需要的letter 那么它可以存放
            // 否则只能舍弃，等着后面的letter，以达到限制条件
            else if(k - (int)res.size() > repetition - used)
                    res.push_back(s[i]);
        }
        return res;
    }
};

int main(){
    Solution s;
//    s.smallestSubsequence("xxxxvvuuosqppppooommmlkjjoihgffddcccbbacdefijlommnnopprtvvwxxyyz",8,'o', 3);
    s.smallestSubsequence("adffhjfmmmmorsfff",6,'f',5);
    cout << 0 << endl;
}