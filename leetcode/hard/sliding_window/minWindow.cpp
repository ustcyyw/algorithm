/**
 * @Time : 2022/7/6-5:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定两个字符串 s 和 t 。返回 s 中包含 t 的所有字符的最短子字符串。如果 s 中不存在符合条件的子字符串，则返回空字符串 "" 。

如果 s 中存在多个符合条件的子字符串，返回任意一个。

 

注意： 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。

 

示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最短子字符串 "BANC" 包含了字符串 t 的所有字符 'A'、'B'、'C'
示例 2：

输入：s = "a", t = "a"
输出："a"
示例 3：

输入：s = "a", t = "aa"
输出：""
解释：t 中两个字符 'a' 均应包含在 s 的子串中，因此没有符合条件的子字符串，返回空字符串。
 

提示：

1 <= s.length, t.length <= 105
s 和 t 由英文字母组成
 

进阶：你能设计一个在 o(n) 时间内解决此问题的算法吗？



来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/M1oyTv
 */
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> countT = vector(256, 0), countSub = vector(256, 0);
        for(char c : t)
            countT[c - 'A']++;
        int left = 0, right = 0, n = s.size(), total = t.size(), count = 0;
        int start = -1, len = 0x7FFFFFFF;
        while (right < n){
            int index = s[right] - 'A';
            if(countSub[index] < countT[index]) count++;
            countSub[index]++;
            while (count == total){
                if(right - left + 1 < len){
                    len = right - left + 1;
                    start = left;
                }
                int tempI = s[left++] - 'A';
                if(countT[tempI] > 0) { // 说明这是一个存在于t中的字母
                    if(--countSub[tempI] < countT[tempI])
                        count--;
                }
            }
            right++;
        }
        return start == -1 ? "" : s.substr(start, len);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}