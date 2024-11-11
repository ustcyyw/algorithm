/**
 * @Time : 2023/11/19-12:29 AM
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
     * 问题考虑有j个鸡蛋 判断i楼的情况 （用dp[i][j]定义该问题的解）
     * 如果首先用一个鸡蛋丢在第t楼 会有两种情况
     * 1. 在第t楼碎了，那么所找楼层在[1, t - 1]上，但是只剩j-1个鸡蛋了
     * 2. 在第t楼没有碎，那么所找楼层在[t + 1, i]，并且鸡蛋依旧有j个
     * 还需要判断 i - t 这么多层的情况 等价于判断楼层[1, i - t]
     * 这两种情况是哪一种不知道，但是为了确保楼层能被确定 一定是二者中最坏的情况也要能确定
     * 并且本次在t楼仍鸡蛋算1次操作
     * 因此 dp[i][j] = min{dp[i][j], max(dp[t - 1][j - 1], dp[i - t][j]) + 1}
     * 需要枚举t从1到i
     * 注意 dp[t - 1][j - 1] 随t增大而增长，t=1的时候很小
     * dp[i - t][j] 随t增大而减小，t=1的时候很大
     * 要使 max(dp[t - 1][j - 1], dp[i - t][j]) 的值最小 应该找到合适的t，让两项最为接近
     * 因此找 dp[t - 1][j - 1] <= dp[i - t][j]的最大t值，此时保证了两项最为接近 且其中一项为全局最小
     */
    int superEggDrop(int k, int n) {
        vector<vector<int>> dp(n + 1, vector(k + 1, INT_MAX));
        dp[0].assign(k + 1, 0);
        for(int i = 1; i <= n; i++) {
            dp[i][1] = i;
            for(int j = 2; j <= k; j++) {
                // 枚举在第t楼尝试丢鸡蛋 坏与不坏两种情况
                // for(int t = 1; t < i; t++)
                //     dp[i][j] = min(dp[i][j], max(dp[t - 1][j - 1], dp[i - t][j]) + 1);
                int lo = 1, hi = i; // 找到 dp[t - 1][j - 1] <= dp[i - t][j]的最大t值
                while(lo < hi) {
                    int mid = (lo + hi + 1) >> 1;
                    if(dp[mid - 1][j - 1] <= dp[i - mid][j]) lo = mid;
                    else hi = mid - 1;
                }
                dp[i][j] = max(dp[lo - 1][j - 1], dp[i - lo][j]) + 1;
            }
        }
        return dp[n][k];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}