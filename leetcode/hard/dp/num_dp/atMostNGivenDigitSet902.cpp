/**
 * @Time : 2022/9/22-1:07 PM
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
     * 本题比起模版有两个变化
     * 1.数字使用范围规定位digits而不是0~9，那么每一位选择数字时对digits枚举即可
     * 2.对数字的使用次数没有任何限制，因此也无需关注前置位的数字选择情况，不需要用mask，因此记忆化也只需要一维
     */
    vector<int> nums;
    string s;
    vector<int> dp;
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        s = to_string(n);
        dp = vector(s.size(), -1);
        for(string d : digits)
            nums.push_back(d[0] - '0');
        return count(0, true, false);
    }

    int count(int i, int limit, int is_num){
        if(i == s.size()) return is_num ? 1 : 0;
        if(!limit && is_num && dp[i] != -1) return dp[i];
        int res = 0;
        if(!is_num) res = count(i + 1, false, false);
        int down = is_num ? 0 : 1, up = limit ? s[i] - '0' : 9;
        for(int num : nums){
            if(num < down) continue;
            if(num > up) break;
            res += count(i + 1, limit && num == up, true);
        }
        if(!limit && is_num) dp[i] =res;
        return res;
    }
};

int main(){
    Solution s;
    vector<string> d = {"1","3","5","7"};
    s.atMostNGivenDigitSet(d, 100);
    cout << 0 << endl;
}