/**
 * @Time : 2022/9/6-8:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。

骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。

有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。

为了尽快到达公主，骑士决定每次只向右或向下移动一步。

 

编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。

例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右 -> 右 -> 下 -> 下，则骑士的初始健康点数至少为 7。

-2 (K)	-3	3
-5	-10	1
10	30	-5 (P)
 

说明:

骑士的健康点数没有上限。

任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/dungeon-game
 */
class Solution {
public:
    /**
     * 二分答案
     * 给定骑士的初始血量，看他到达右下角时的最大血量是否大于0
     * 在路径上某一点变为0或者负数后，该点就不能再参与转移方程的计算，因为骑士已经挂掉了
     *
     * ac 40ms
     */
//    int n, m;
//    int calculateMinimumHP(vector<vector<int>>& dungeon) {
//        n = dungeon.size(), m = dungeon[0].size();
//        long lo = 1, hi = INT_MAX;
//        while (lo < hi){
//            long mid = (hi + lo) >> 1;
//            if(check(dungeon, mid)) hi = mid;
//            else lo = mid + 1;
//        }
//        return lo;
//    }
//
//    bool check(vector<vector<int>>& dungeon, long val){
//        vector<vector<long>> dp(n, vector(m, -1l));
//        dp[0][0] = val + dungeon[0][0];
//        for(int i = 0; i < n; i++){
//            for(int j = 0; j < m; j++){
//                if(i - 1 >= 0 && dp[i - 1][j] > 0)
//                    dp[i][j] = dungeon[i][j] + dp[i - 1][j];
//                if(j - 1 >= 0 && dp[i][j - 1] > 0)
//                    dp[i][j] = max(dp[i][j], dungeon[i][j] + dp[i][j - 1]);
//            }
//        }
//        return dp[n - 1][m - 1] > 0;
//    }

    /**
     * 参考评论区解法
     *
     * 正向来做，需要记录到达某个点的路径和最大值，还记录到达某点所需要的健康最小值
     * 有两个维度的决策
     * 并且路径的选取还和后续的情况相关，不满足「无后效性」的
     *
     * 因此要反向思考。定义状态dp[i][j]是到达终点需要的最小健康值
     * dp[i + 1][j], dp[i][j + 1]是此点到达终点的下一步
     * 暂且不管dungeon[i][j]的影响
     * 那必然是 dp[i + 1][j] 和 dp[i][j + 1]哪一个到达终点需要的健康值最小，就走哪边
     * 于是dp[i][j] = min(dp[i + 1][j], dp[i][j + 1])
     *
     * 然后再考虑dungeon[i][j]的影响
     * 如果dungeon[i][j] > 0,在(i,j)这个点回复健康
     * 所从(i,j)这个点走到终点需要的最小健康值还可以比dp[i][j]少dungeon[i][j]
     * 也就是 dp[i][j] -= dungeon[i][j]
     * 如果dungeon[i][j] < 0,在(i,j)这个点扣掉健康
     * 所从(i,j)这个点走到终点需要的最小健康值必须增大abs(dungeon[i][j])
     * 也就是 dp[i][j] += abs(dungeon[i][j])，等价于dp[i][j] -= dungeon[i][j]
     * 因此无论dungeon[i][j]是正还是负，都有dp[i][j] -= dungeon[i][j]
     *
     * 另外要注意，骑士任何时候健康值都要大于0，因此任何一个点骑士受dungeon[i][j]影响前后，其健康值都至少为1
     * 必须有dp[i][j] >= 1
     */
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size(), m = dungeon[0].size();
        vector<vector<int>> dp(n, vector(m, 1));
        dp[n - 1][m - 1] = max(1 - dungeon[n - 1][m - 1], 1);
        for(int i = n - 1; i >= 0; i--){
            for(int j = m - 1; j >= 0; j--){
                int t1 = j + 1 < m ? dp[i][j + 1] : INT_MAX;
                int t2 = i + 1 < n ? dp[i + 1][j] : INT_MAX;
                dp[i][j] = max(min(t1, t2) - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}