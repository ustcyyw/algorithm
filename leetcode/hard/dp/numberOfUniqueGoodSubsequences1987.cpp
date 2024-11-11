/**
 * @Time : 2023/4/25-9:08 PM
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
     * 为了简便处理前导0的情况 可以从右往左遍历 考虑当前元素是否添加到子序列中
     * 定义
     * dp[i][0]: 从右往左，截止索引为i的位置，s[i,n - 1]上以0开头的子序列的数目
     * dp[i][1]: 从右往左，截止索引为i的位置，s[i,n - 1]上以1开头的子序列的数目
     *
     * s[i] == '0' 则有 dp[i][0] = dp[i + 1][1] + dp[i + 1][0] + 1
     * 最后一项+1，表示当前元素自己构成的序列，也是以 0 开头的一个子序列
     * 第一项和第二项 分别是将当前的0，添加到前置以1或者 0 开头的子序列前面
     * 那么这些序列 要么是01开头，要么是00开头，或者就是当前的一个0 不会出现重复
     *
     * 否则 dp[i][1] = dp[i + 1][1] + dp[i + 1][0] + 1 （同理）
     * 最终答案要取1开头的，也就是dp[0][1]
     * 但是不要忘了 如果s中存在0，那么还有'0'这个特殊的子序列，合法但不以1开头。
     */
    int numberOfUniqueGoodSubsequences(string binary) {
        int n = binary.size(), mod = 1e9 + 7, zero = 0;
        vector<vector<long>> dp(n + 1, vector(2, 0l));
        for(int i = n - 1; i >= 0; i--) {
            dp[i][0] = dp[i + 1][0], dp[i][1] = dp[i + 1][1];
            if(binary[i] == '0') {
                dp[i][0] = (1 + dp[i + 1][0] + dp[i + 1][1]) % mod;
                zero = 1;
            }
            else dp[i][1] = (1 + dp[i + 1][0] + dp[i + 1][1]) % mod;
        }
        return (dp[0][1] + zero) % mod;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}