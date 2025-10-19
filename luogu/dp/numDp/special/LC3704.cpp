/**
 * @Time : 2025/10/17-15:19
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3704 2429 数位dp
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31, N = 1e5 + 5;

class Solution {
public:
    /*
     * dp[i][1/0]: 第i位进行加法的时候，是否会导致进位
     * dp[i][j]:
     * 从dp[i+1][0]转移时 ai + bi = j * 10 + s[i]
     * 从dp[i+1][1]转移时 ai + bi + 1 = j * 10 + s[i]
     * 枚举ai从1到9, 计算bi, 要bi不为0且范围是[1,9]才行
     * 这是一般的转移方程。但是有时候 取的两个数数位不一致 比如11和3498
     * 那么就需要两个变量来标志a和b是否已经有效（一般的数位dp只考虑一个数，就只需要一个标志）
     */
    string s;
    vector<vector<ll>> dp;
    long long countNoZeroPairs(long long n) {
        s = to_string(n);
        dp = vector(s.size(), vector(2, -1ll));
        return count(0, 0, false, false);
    }
    // num1和num2分别表示a和b是否已经取过数位
    ll count(int i, int j, bool num1, bool num2){
        // 递归结束的时候 实际上已经不是有效数位 不可能由这个不存在的数位加法进位 所以j必须是0
        if(i == s.size()) return num1 && num2 && j == 0 ? 1 : 0;
        if(num1 && num2 && dp[i][j] != -1) return dp[i][j];
        ll cnt = 0;
        int need = j * 10 + s[i] - '0';
        if(!num1 && !num2) { // 两个数当前位都还没有数字 考虑让ab都不取数
            if(i == 0 && s[i] == '1') { // 可以依赖下一位进行进位的情况
                cnt += count(i + 1, 1, false, false);
            }
        }
        if(!num1) { // a继续不取数 让b来取数的情况
            if(check(need - 1)) cnt += count(i + 1, 1, false, true);
            if(check(need)) cnt += count(i + 1, 0, false, true);
        }
        if(!num2) { // b继续不取数 让a来取数的情况
            if(check(need - 1)) cnt += count(i + 1, 1, true, false);
            if(check(need)) cnt += count(i + 1, 0, true, false);
        }
        for(int ai = 1; ai <= 9; ai++) {
            int bi1 = need - ai, bi2 = need - ai - 1;
            if(check(bi1)) cnt += count(i + 1, 0, true, true);
            if(check(bi2)) cnt += count(i + 1, 1, true, true);
        }
        if(num1 && num2) dp[i][j] = cnt;
        return cnt;
    }

    bool check(int num) {
        return num > 0 && num <= 9;
    }
};