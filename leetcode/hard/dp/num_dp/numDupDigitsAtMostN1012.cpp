/**
 * @Time : 2022/9/22-8:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 本题和模板的差异
     * 需要记录在选的过程中有没有选到重复数组，多一个bool dup表示是否已经出现重复
     * 如果在上一个位置已经有重复了，那么递归继续传递dup = true
     * 如果当前位置选择到数字，和前置位置的数字集合有重复，也要向下传递 dup = true
     * 因此dup = dup |  ((mask & t) > 0, t = 1 << j
     * 记忆化的时候也需要多一个维度来表示dup的情况
     */
    int m;
    string s;
    vector<vector<vector<int>>> dp;
    int numDupDigitsAtMostN(int n) {
        s = to_string(n);
        m = s.size();
        dp = vector(2, vector(m, vector(1 << 10, -1)));
        return count(0, 0, true, false, false);
    }

    int count(int i, int mask, bool limit, bool is_num, bool dup){
        if(i == m) return is_num && dup;
        if(!limit && is_num && dp[dup][i][mask] != -1) return dp[dup][i][mask];
        int res = 0;
        if(!is_num) res = count(i + 1, mask, false, false, false);
        int down = is_num ? 0 : 1, up = limit ? s[i] - '0' : 9;
        for(int j = down; j <= up; j++){
            int t = 1 << j, next_mask = mask | t;
            res += count(i + 1, next_mask, limit && j == up, true, dup | ((mask & t) > 0));
        }
        if(!limit && is_num) dp[dup][i][mask] = res;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}