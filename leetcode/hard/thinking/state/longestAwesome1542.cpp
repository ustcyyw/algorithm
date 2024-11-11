/**
 * @Time : 2023/2/27-10:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给你一个字符串 s 。请返回 s 中最长的 超赞子字符串 的长度。

「超赞子字符串」需满足满足下述两个条件：

该字符串是 s 的一个非空子字符串
进行任意次数的字符交换后，该字符串可以变成一个回文字符串
 

示例 1：

输入：s = "3242415"
输出：5
解释："24241" 是最长的超赞子字符串，交换其中的字符后，可以得到回文 "24142"
示例 2：

输入：s = "12345678"
输出：1
示例 3：

输入：s = "213123"
输出：6
解释："213123" 是最长的超赞子字符串，交换其中的字符后，可以得到回文 "231132"
示例 4：

输入：s = "00"
输出：2
 

提示：

1 <= s.length <= 10^5
s 仅由数字组成

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/find-longest-awesome-substring
 */
class Solution {
public:
    /*
     * 超赞子字符串：进行任意次数的字符交换后，该字符串可以变成一个回文字符串
     * 可以进行任意两个字符的交换，相当于可以将子串中的字符随意排
     * 于是要构成回文串，就只需要出现过的字符，至多有一个字符出现了奇数次
     * 因此，关注子串中字符出现次数的奇偶即可，奇偶性正好是两个状态
     * 出现偶数次，可以用状态0表示，出现奇数次用状态1表示
     *
     * 先考虑只有一个字符的字符串
     * 比如序列 3 3 3 3 3，对应的奇偶状态是 1 0 1 0 1
     * 相同状态之间(指左开右闭，例如第一个1和最后一个1对应的区间(0,4]上，3出现了4次)3出现的次数是偶数次
     * 不同状态之间3出现的次数是奇数次
     *
     * 考虑0-9这10个数字，就需要10个二进制位来表示
     * 枚举当前状态 status
     * 1.子串中每个数字出现偶数次，就是找s的相同状态
     * 2.子串中有一个数字出现奇数次，其它数字出现偶数次
     *   就枚举出现奇数次的数字是哪一个，让代表该数字的位取反(异或操作)，其余位不变，找这个状态的相同状态
     */
    int longestAwesome(string s) {
        unordered_map<int, int> map;
        map[0] = -1; // 空字符串，设置哨兵
        int status = 0, res = 1, n = s.size();
        for(int i = 0; i < n; i++){
            status ^= 1 << (s[i] - '0');
            res = max(res, map.count(status) ? i - map[status] : -1);
            for(int j = 0; j < 10; j++){
                int temp = status ^ (1 << j);
                res = max(res, map.count(temp) ? i - map[temp] : -1);
            }
            if(!map.count(status)) map[status] = i;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}