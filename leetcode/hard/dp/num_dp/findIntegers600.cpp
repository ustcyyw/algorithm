/**
 * @Time : 2022/9/23-4:36 PM
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
     * 本题与模版的差异
     * 0.本题是二进制下的数位dp，只能选1或者0，要先把n转换成二进制表示
     * 1.本题只规定不能出现连续的1，但是不限制0和1各能取多少次，因此不需要mask，而是需要一个bool变量pre_one
     * pre_one 为 true表示在选取第i位时，第i-1位是1
     * 因此dp是二维的，有一个维度表示pre_one的情况
     * 2.本题可以取0，但是模版的写法，取0是不记数的，因此返回的时候要+1
     */
    int m;
    vector<int> nums;
    vector<vector<int>> dp;
    int findIntegers(int n) {
        bitset<32> aux(n);
        for(int i = aux.size() - 1, flag = 0; i >= 0; i--){
            if(aux[i]) flag = true;
            if(flag) nums.push_back(aux[i]);
        }
        m = nums.size();
        dp = vector(m, vector(2, -1));
        return count(0, true, false, false) + 1;
    }

    int count(int i, bool limit, bool is_num, bool pre_one){
        if(i == m) return is_num;
        if(!limit && is_num && dp[i][pre_one] != -1) return dp[i][pre_one];
        int res = 0;
        if(!is_num) res = count(i + 1, false, false, false);
        int down = is_num ? 0 : 1, up = limit ? nums[i] : 1;
        for(int j = down; j <= up; j++){
            bool next_limit = limit && j == nums[i];
            // 要保证不能出现连续的1，那么j==0或者j==1时要求前置位没有选取1，这样才能计数
            if(j == 0) res += count(i + 1, next_limit, true, false);
            else if(!pre_one) res += count(i + 1, next_limit, true, true);
        }
        if(!limit && is_num) dp[i][pre_one] = res;
        return res;
    }
};

int main(){
    Solution s;
    s.findIntegers(5);
    cout << 0 << endl;
}