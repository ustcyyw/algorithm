/**
 * @Time : 2023/7/31-10:06 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 给你两个正整数 low 和 high ，都用字符串表示，请你统计闭区间 [low, high] 内的 步进数字 数目。

如果一个整数相邻数位之间差的绝对值都 恰好 是 1 ，那么这个数字被称为 步进数字 。

请你返回一个整数，表示闭区间 [low, high] 之间步进数字的数目。

由于答案可能很大，请你将它对 109 + 7 取余 后返回。

注意：步进数字不能有前导 0 。

 

示例 1：

输入：low = "1", high = "11"
输出：10
解释：区间 [1,11] 内的步进数字为 1 ，2 ，3 ，4 ，5 ，6 ，7 ，8 ，9 和 10 。总共有 10 个步进数字。所以输出为 10 。
示例 2：

输入：low = "90", high = "101"
输出：2
解释：区间 [90,101] 内的步进数字为 98 和 101 。总共有 2 个步进数字。所以输出为 2 。
 

提示：

1 <= int(low) <= int(high) < 10100
1 <= low.length, high.length <= 100
low 和 high 只包含数字。
low 和 high 都不含前导 0 。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/count-stepping-numbers-in-range
 */
#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
class Solution {
public:
    int countSteppingNumbers(string low, string high) {
        long res = count(high) - count(low) + mod;
        if(check(low)) res++;
        return res % mod;
    }

    long count(string& s) {
        int n = s.size();
        vector<vector<long>> cache(n, vector(10, -1l));
        function<long(int, int, bool, bool)> dfs = [&](int i, int pre, bool limit, bool is_num) -> long {
            if(i == n) return is_num;
            if(!limit && is_num && cache[i][pre] != -1) return cache[i][pre];
            long res = 0;
            if(!is_num) {
                res = dfs(i + 1, pre, false, false);
                int t = i == 0 ? s[0] - '0' : 9;
                for(int j = 1; j <= t; j++)
                    res += dfs(i + 1, j, (i == 0 || limit) && j == t, true);
            } else {
                int up = s[i] - '0';
                if(pre + 1 <= 9 && (!limit || pre + 1 <= up))
                    res += dfs(i + 1, pre + 1, limit && pre + 1 == up, true);
                if(pre - 1 >= 0 && (!limit || pre - 1 <= up))
                    res += dfs(i + 1, pre - 1, limit && pre - 1 == up, true);
            }
            res %= mod;
            if(!limit && is_num) cache[i][pre] = res;
            return res;
        };
        return dfs(0, -1, true, false) % mod;
    }

    bool check(string& s) {
        for(int i = 1; i < s.size(); i++) {
            if(abs(s[i] - s[i - 1]) != 1) return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}