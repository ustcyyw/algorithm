/**
 * @Time : 2022/9/23-12:44 PM
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
     * 本题与模版的差异在于：
     * 1.没有限定某个数字的选取次数，因此mask不需要
     * 2.要求的是数字出现的次数，而不是满足题意的数的计数
     * 关于第二点，可以用回溯的做法去思考
     * 在递归到结束时，需要知道当前选取的数字中有多少个1，因此最方便的做法就是带着一个变量 one
     * one 表示：截止到第i-1位，选取的1的数量
     * 前置位如果选取了1个1，那么前置位的方案不论是 123 321 71 213等任何不会导致后续超过n的
     * 对后续的所有选择方案，都是贡献1个1
     * 因此在做记忆化的时候，只需要关注1的选取个数，以及模版中的数位i即可。
     */
    string s;
    vector<vector<int>> dp;
    int m;
    int countDigitOne(int n) {
        s = to_string(n);
        m = s.size();
        dp = vector(m, vector(m + 1, - 1));
        return count(0, true, false, 0);
    }

    int count(int i, bool limit, bool is_num, int one){
        if(i == m) return is_num ? one : 0;
        if(!limit && is_num && dp[i][one] != -1) return dp[i][one];
        int cnt = 0;
        if(!is_num) cnt = count(i + 1, false, false, one);
        int down = is_num ? 0 : 1, up = limit ? s[i] - '0' : 9;
        for(int j = down; j <= up; j++){
            int next_one = j == 1 ? one + 1 : one;
            cnt += count(i + 1, limit && j == up, true, next_one);
        }
        if(!limit && is_num) dp[i][one] = cnt;
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}