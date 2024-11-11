/**
 * @Time : 2022/8/14-8:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个字符串 s ，检查是否能重新排布其中的字母，使得两相邻的字符不同。

返回 s 的任意可能的重新排列。若不可行，返回空字符串 "" 。

 

示例 1:

输入: s = "aab"
输出: "aba"
示例 2:

输入: s = "aaab"
输出: ""
 

提示:

1 <= s.length <= 500
s 只包含小写字母


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/reorganize-string
 */
class Solution {
public:
    /**
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：6.2 MB, 在所有 C++ 提交中击败了28.78%的用户
     *
     * 形象的说就是多元生长
     * 假设最多的字母有n个，那么就将他们排在n行的首位，铺满第一列
     * 然后依次用其它字母去在每一行添加一个，铺满第二列，这样就保证n行合并之后，最多的字母不会相邻
     * 还剩的每一种字母再去分别铺第三列，第四列，第五列(肯定铺不满)...
     * 合并之后也保证他们被最多的字母给分割开了
     *
     * 举个例子 原字符串有5个a， a:5
     * b:3, c:3, d:2, e:2, f:1
     * 先铺第一列
     * a
     * a
     * a
     * a
     * a
     * 再铺第二列
     * a b
     * a b
     * a b
     * a c
     * a c
     * 剩余的每一种字母分别去铺后续的列
     * a b c d e f
     * a b   d e
     * a b
     * a c
     * a c
     */
    string reorganizeString(string s) {
        vector<pair<char, int>> chars(26);
        for(int i = 0; i < 26; i++)
            chars[i] = make_pair((char)(i + 'a'), 0);
        for(char c : s)
            chars[c - 'a'].second++;
        sort(chars.begin(), chars.end(),
             [](auto& a, auto& b) -> bool {return a.second < b.second;});
        int sum = 0, max_val = chars[25].second;
        for(int i = 0; i < 25; i++)
            sum += chars[i].second;
        if(sum + 1 < max_val) return ""; // 其余所有字母全用去隔开最多的字母还不够用
        vector<string> parts;
        parts.assign(max_val, {});
        for(int i = 0, j = 24; i < max_val; i++){
            parts[i].push_back(chars[25].first);
            while (j >= 0 && chars[j].second == 0) j--;
            if(j < 0) break; // 最多的字母是其它字母之和+1的情况
            parts[i].push_back(chars[j].first);
            chars[j].second--;
        }
        if(parts[max_val - 1].empty()) // 可能最后一行的开头字母还没放置
            parts[max_val - 1].push_back(chars[25].first);
        for(int j = 24; j >= 0; j--){
            for(int i = 0; i < max_val && chars[j].second > 0; i++){
                parts[i].push_back(chars[j].first);
                chars[j].second--;
            }
        }
        string res;
        for(string& part : parts) res += part;
        return res;
    }
};

int main(){
    Solution s;
    s.reorganizeString("aab");
    cout << 0 << endl;
}