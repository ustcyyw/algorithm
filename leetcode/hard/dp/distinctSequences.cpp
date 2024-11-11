/**
 * @Time : 2022/6/27-5:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数 n 。你需要掷一个 6 面的骰子 n 次。请你在满足以下要求的前提下，求出 不同 骰子序列的数目：

序列中任意 相邻 数字的 最大公约数 为 1 。
序列中 相等 的值之间，至少有 2 个其他值的数字。正式地，如果第 i 次掷骰子的值 等于 第 j 次的值，那么 abs(i - j) > 2 。
请你返回不同序列的 总数目 。由于答案可能很大，请你将答案对 109 + 7 取余 后返回。

如果两个序列中至少有一个元素不同，那么它们被视为不同的序列。

 

示例 1：

输入：n = 4
输出：184
解释：一些可行的序列为 (1, 2, 3, 4) ，(6, 1, 2, 3) ，(1, 2, 3, 1) 等等。
一些不可行的序列为 (1, 2, 1, 3) ，(1, 2, 3, 6) 。
(1, 2, 1, 3) 是不可行的，因为第一个和第三个骰子值相等且 abs(1 - 3) = 2 （下标从 1 开始表示）。
(1, 2, 3, 6) i是不可行的，因为 3 和 6 的最大公约数是 3 。
总共有 184 个不同的可行序列，所以我们返回 184 。
示例 2：

输入：n = 2
输出：22
解释：一些可行的序列为 (1, 2) ，(2, 1) ，(3, 2) 。
一些不可行的序列为 (3, 6) ，(2, 4) ，因为最大公约数不为 1 。
总共有 22 个不同的可行序列，所以我们返回 22 。
 

提示：

1 <= n <= 104


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/number-of-distinct-roll-sequences
 */
class Solution {
public:
    /**
     * dp[t][i][j] 表示第t次数字为j且前一个数字为i的序列数
     * dp[t][i][j] 的计算：
     * 首先在t位置需要枚举i，j的所有组合，一共36组，但是不满足要求1的组合，方案数就是0(跳过计算)
     * 因此 relations[j].find(i) != relations[j].end() 满足这个条件的才需要计算
     * dp[t] 显然和 dp[t - 1]相关，且dp[t][i][j]，的t-1位置一定是i
     * 所以要枚举dp[t-1][k][i] for k in [1, 6], (i,k)如果不合法 dp[i-1][k][i] = 0，可以直接加上
     * 只需要满足第二个条件即可 因此要做判断if(k != j)，满足才进行相加
     *
     * 时间复杂度 最坏是216 * 10 ^ 4
     */
    int mod = 1000000007;
    vector<unordered_set<int>> relations = {{},{2,3,4,5,6},{1,3,5},{1,2,4,5},{1,3,5},{1,2,3,4,6},{1,5}};
    int distinctSequences(int n) {
        if(n == 1) return 6;
        vector<vector<vector<long>>> dp = vector(n + 1, vector(7, vector(7, 0l)));
        for(int i = 1; i <= 6; i++){
            for(int j = 1; j <= 6; j++){
                if(relations[j].find(i) != relations[j].end())
                    dp[2][i][j] = 1l;
            }
        }
        for(int t = 3; t <= n; t++){
            vector<vector<long>>& cur = dp[t], pre = dp[t - 1];
            for(int i = 1; i <= 6; i++){
                for(int j = 1; j <= 6; j++){
                    if(relations[j].find(i) != relations[j].end()){
                        for(int k = 1; k <= 6; k++)
                            if(k != j) cur[i][j] += pre[k][i];
                    }
                    cur[i][j] %= mod;
                }
            }
        }
        long res = 0l;
        for(int i = 1; i <= 6; i++){
            for(int j = 1; j <= 6; j++) {
                res += dp[n][i][j];
            }
        }
        return (int)(res % mod);
    }
};

int main(){
    Solution s;
    s.distinctSequences(3);

    cout << 0 << endl;
}