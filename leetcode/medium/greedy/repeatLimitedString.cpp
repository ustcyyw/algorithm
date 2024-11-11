/**
 * @Time : 2022/8/23-4:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个字符串 s 和一个整数 repeatLimit ，用 s 中的字符构造一个新字符串 repeatLimitedString ，使任何字母 连续 出现的次数都不超过 repeatLimit 次。你不必使用 s 中的全部字符。

返回 字典序最大的 repeatLimitedString 。

如果在字符串 a 和 b 不同的第一个位置，字符串 a 中的字母在字母表中出现时间比字符串 b 对应的字母晚，则认为字符串 a 比字符串 b 字典序更大 。如果字符串中前 min(a.length, b.length) 个字符都相同，那么较长的字符串字典序更大。

 

示例 1：

输入：s = "cczazcc", repeatLimit = 3
输出："zzcccac"
解释：使用 s 中的所有字符来构造 repeatLimitedString "zzcccac"。
字母 'a' 连续出现至多 1 次。
字母 'c' 连续出现至多 3 次。
字母 'z' 连续出现至多 2 次。
因此，没有字母连续出现超过 repeatLimit 次，字符串是一个有效的 repeatLimitedString 。
该字符串是字典序最大的 repeatLimitedString ，所以返回 "zzcccac" 。
注意，尽管 "zzcccca" 字典序更大，但字母 'c' 连续出现超过 3 次，所以它不是一个有效的 repeatLimitedString 。
示例 2：

输入：s = "aababab", repeatLimit = 2
输出："bbabaa"
解释：
使用 s 中的一些字符来构造 repeatLimitedString "bbabaa"。
字母 'a' 连续出现至多 2 次。
字母 'b' 连续出现至多 2 次。
因此，没有字母连续出现超过 repeatLimit 次，字符串是一个有效的 repeatLimitedString 。
该字符串是字典序最大的 repeatLimitedString ，所以返回 "bbabaa" 。
注意，尽管 "bbabaaa" 字典序更大，但字母 'a' 连续出现超过 2 次，所以它不是一个有效的 repeatLimitedString 。
 

提示：

1 <= repeatLimit <= s.length <= 105
s 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/construct-string-with-repeat-limit
 */
class Solution {
public:
    /**
     * 执行用时：72 ms, 在所有 C++ 提交中击败了45.95%的用户
     * 内存消耗：23.8 MB, 在所有 C++ 提交中击败了82.88%的用户
     */
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> count = vector(26, 0);
        for(char c : s)
            count[c - 'a']++;
        string res;
        for(int i = 25, j = 25; j >= 0; ){
            while (i >= 0 && count[i] == 0) i--;
            if(i == -1) break;
            int time = count[i] / repeatLimit + (count[i] % repeatLimit == 0 ? 0 : 1);
            char c = (char)(i + 'a');
            for(int k = 0; k < time; k++){
                for(int l = 0; l < repeatLimit && count[i] > 0; l++){
                    res.push_back(c);
                    count[i]--;
                }
                j = i - 1;
                while (j >= 0 && count[j] == 0) j--;
                if(j == -1) break;
                if(count[i] != 0){
                    res.push_back((char)(j + 'a'));
                    count[j]--;
                }
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}