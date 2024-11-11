/**
 * @Time : 2022/8/22-8:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你两个字符串 s 和 t 。在一步操作中，你可以给 s 或者 t 追加 任一字符 。

返回使 s 和 t 互为 字母异位词 所需的最少步骤数。

字母异位词 指字母相同但是顺序不同（或者相同）的字符串。

 

示例 1：

输入：s = "algorithm", t = "coats"
输出：7
解释：
- 执行 2 步操作，将 "as" 追加到 s = "algorithm" 中，得到 s = "leetcodeas" 。
- 执行 5 步操作，将 "leede" 追加到 t = "coats" 中，得到 t = "coatsleede" 。
"leetcodeas" 和 "coatsleede" 互为字母异位词。
总共用去 2 + 5 = 7 步。
可以证明，无法用少于 7 步操作使这两个字符串互为字母异位词。
示例 2：

输入：s = "night", t = "thing"
输出：0
解释：给出的字符串已经互为字母异位词。因此，不需要任何进一步操作。
 

提示：

1 <= s.length, t.length <= 2 * 105
s 和 t 由小写英文字符组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii
 */
class Solution {
public:
    int minSteps(string s, string t) {
        vector<int> sc = count(s), tc = count(t);
        int res = 0;
        for(int i = 0; i < 26; i++)
            res += abs(sc[i] - tc[i]);
        return res;
    }

    vector<int> count(string& s){
        vector<int> count = vector(26, 0);
        for(char c : s)
            count[c - 'a']++;
        return count;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}