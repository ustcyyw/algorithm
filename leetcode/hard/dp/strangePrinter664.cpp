/**
 * @Time : 2023/3/21-1:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 看数据范围和求最小值，比较容易猜到区间dp
     * 问题从简单入手
     * ab需要打印两次
     * aba也需要打印两次，就是在打印ab的时候一次性打印了aaa，再将中间一个字母打印成b
     * 但是abab需要打印3次，得先打印aba，再打印b；或者先打印a，再打印aba
     *
     * 当两端字母相同时，可以在打印首字母的时候，将右端点字母也打印出来，减少一次打印次数
     * 但如果两端字母不同，就需要枚举区间但切割点 找最优的切割方式
     */
    vector<vector<int>> cache;
    int strangePrinter(string s) {
        int n = s.size();
        cache = vector(n, vector(n, -1));
        return min_step(s, 0, n - 1);
    }

    int min_step(string& s, int lo, int hi){
        if(lo > hi) return 0;
        if(lo == hi) return 1;
        if(cache[lo][hi] != -1) return cache[lo][hi];
        int res = 101;
        if(s[lo] == s[hi])  // 两头字母相同，一种方案是中间部分是在这个字母之上覆盖
            res = min_step(s, lo, hi - 1);
        for(int i = lo; i < hi; i++)
            res = min(res, min_step(s, lo, i) + min_step(s, i + 1, hi));
        cache[lo][hi] = res;
        return res;
    }

    /*
     * 区间dp三段式
     * 1.枚举区间长度
     * 2.枚举区间左端点，根据长度确定右端点
     * 3.枚举当前区间的切割点
     */
    int strangePrinter2(string s){
        int n = s.size();
        vector<vector<int>> dp(n, vector(n, 1001));
        for(int i = 0; i < n; i++)
            dp[i][i] = 1; // 边界条件 只有一个字母的时候，也需要打印一次
        for(int len = 2; len <= n; len++){
            for(int i = 0; i + len - 1 < n; i++){
                int j = i + len - 1;
                if(s[i] == s[j]) dp[i][j] = dp[i][j - 1];
                else {
                    for(int k = i; k < j; k++)
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}