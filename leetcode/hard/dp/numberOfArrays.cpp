/**
 * @Time : 2022/7/23-11:08 AM
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
     * dp[i]表示在索引i处切分，区间[0,i]上合法的组合数量（i处的数字归左边区间）
     * 切分的时候要保证：第i+1处的数字不是0，否则就直接定为dp[i] = 0，表示这里不能切，是0种组合方式
     * 对于j < i,并且[j + 1, i]上的数字是 小于等于k的， dp[i] += dp[j]
     * 由于k最大是1e9，因此向前遍历的区间长度最长为10
     *
     * 执行用时：52 ms, 在所有 C++ 提交中击败了67.07%的用户
     * 内存消耗：14.5 MB, 在所有 C++ 提交中击败了17.07%的用户
     */
    int mod = 1e9 + 7;
    int numberOfArrays(string s, int k) {
        s = "0" + s;
        int n = s.size(), m = to_string(k).size(); // k有多少位
        vector<long long> dp = vector(n, 0ll);
        if(s[1] - '0' > k) return 0;
        dp[0] = 1;
        for(int i = 1; i < n; i++){
            if(i < n - 1 && dp[i + 1] == '0') continue;
            for(int j = i - 1; j >= 0 && i - j <= m; j--){
                // [j + 1, i]上的数字不能有前导0，并且应<=k(位数不足m的时候一定小于k)
                if(s[j + 1] == '0' || (i - j == m && !check(s, k, j + 1, i))) continue;
                dp[i] = (dp[i] + dp[j]) % mod;
            }
        }
        return (int)dp[n - 1];
    }

    bool check(string& s, int k, int lo, int hi){
        long num = 0;
        for(int i = lo; i <= hi; i++){
            num *= 10;
            num += s[i] - '0';
        }
        return num <= k;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}