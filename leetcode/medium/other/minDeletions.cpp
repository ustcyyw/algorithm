/**
 * @Time : 2022/9/12-3:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 如果字符串 s 中 不存在 两个不同字符 频次 相同的情况，就称 s 是 优质字符串 。

给你一个字符串 s，返回使 s 成为 优质字符串 需要删除的 最小 字符数。

字符串中字符的 频次 是该字符在字符串中的出现次数。例如，在字符串 "aab" 中，'a' 的频次是 2，而 'b' 的频次是 1 。

 

示例 1：

输入：s = "aab"
输出：0
解释：s 已经是优质字符串。
示例 2：

输入：s = "aaabbbcc"
输出：2
解释：可以删除两个 'b' , 得到优质字符串 "aaabcc" 。
另一种方式是删除一个 'b' 和一个 'c' ，得到优质字符串 "aaabbc" 。
示例 3：

输入：s = "ceabaacb"
输出：2
解释：可以删除两个 'c' 得到优质字符串 "eabaab" 。
注意，只需要关注结果字符串中仍然存在的字符。（即，频次为 0 的字符会忽略不计。）
 

提示：

1 <= s.length <= 105
s 仅含小写英文字母

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-deletions-to-make-character-frequencies-unique
 */
class Solution {
public:
    int minDeletions(string s) {
        vector<int> cnt(26, 0);
        for(char c : s)
            cnt[c - 'a']++;
        int res = 0;
        map<int, int> map;
        for(int num : cnt)
            if(num > 0) map[num]++;
        while (!map.empty()){
            auto top = map.rbegin();
            if(top->second > 1) {
                res += top->second - 1;
                map[top->first - 1] += top->second - 1;
            }
            map.erase(map.find(top->first));
        }
        return res;
    }
};

int main(){
    Solution s;
    s.minDeletions("aab");
    cout << 0 << endl;
}