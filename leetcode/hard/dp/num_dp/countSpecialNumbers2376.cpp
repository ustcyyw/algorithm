/**
 * @Time : 2022/9/21-11:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string s;
    vector<vector<int>> dp;
    int countSpecialNumbers(int n){
        s = to_string(n);
        dp = vector(s.size(), vector((1 << 10), - 1));
        // 初状态，要选第0位数字i = 0,；前面没有选择任何数字，数字集合的状态是mask = 0
        // 第0位数字不能超过s[0],所以limit=true；前面还没有任何数字，is_num = false
        return count(0, 0, true, false);
    }
    int count(int i, int mask, bool limit, bool is_num){
        if(i == s.size()) return is_num ? 1 : 0;
        if(!limit && is_num && dp[i][mask] != -1) return dp[i][mask];
        int cnt = 0;
        if(!is_num) // 前置位没有选择数字，当前位的一种方案就是也不选择，那么is_num继续为false
            cnt = count(i + 1, mask, false, false);
        int up = limit ? s[i] - '0' : 9, down = is_num ? 0 : 1;
        for(int j = down; j <= up; j++){
            if(condition(j, mask)){
                int next_mask = (1 << j) | mask; // 更新所选集合
                cnt += count(i + 1, next_mask, limit && j == up, true);
            }
        }
        if(!limit && is_num) dp[i][mask] = cnt;
        return cnt;
    }

    // 本题要求不出现相同的数字，因此与mask不能有相交
    bool condition(int j, int mask){
        return (mask & (1 << j)) == 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}