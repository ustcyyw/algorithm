/**
 * @Time : 2022/6/30-11:28 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 如果一个密码满足以下所有条件，我们称它是一个 强 密码：

它有至少 8 个字符。
至少包含 一个小写英文 字母。
至少包含 一个大写英文 字母。
至少包含 一个数字 。
至少包含 一个特殊字符 。特殊字符为："!@#$%^&*()-+" 中的一个。
它 不 包含 2 个连续相同的字符（比方说 "aab" 不符合该条件，但是 "aba" 符合该条件）。
给你一个字符串 password ，如果它是一个 强 密码，返回 true，否则返回 false 。

 

示例 1：

输入：password = "IloveLe3tcode!"
输出：true
解释：密码满足所有的要求，所以我们返回 true 。
示例 2：

输入：password = "Me+You--IsMyDream"
输出：false
解释：密码不包含数字，且包含 2 个连续相同的字符。所以我们返回 false 。
示例 3：

输入：password = "1aB!"
输出：false
解释：密码不符合长度要求。所以我们返回 false 。
 

提示：

1 <= password.length <= 100
password 包含字母，数字和 "!@#$%^&*()-+" 这些特殊字符。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/strong-password-checker-ii
 */
class Solution {
public:
    unordered_set<char> set = {'!','@','#','$','%','^','&','*','(',')','-','+'};
    bool strongPasswordCheckerII(string password) {
        int n = password.size();
        if(n < 8) return false;
        bool num = false, lower = false, upper = false, special = false;
        for(int i = 0; i < n; i++){
            char c = password[i];
            if(i - 1 >= 0 && password[i - 1] == c) return false;
            if(c >= '0' && c <= '9') num = true;
            if(c >= 'a' && c <= 'z') lower = true;
            if(c >= 'A' && c <= 'Z') upper = true;
            if(!set.count(c)) special = true;
        }
        return num && lower && upper && special;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}