/**
 * @Time : 2023/12/19-4:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
 * 前缀和
 * 一维前缀和：sum[i] 可以理解为数轴上，线段[0,i]一共存在多少个点
 * 二维前缀和：sum[i][j] 可以理解为平面上，矩形区域[0,i] x [0,j]一共存在多少个点
 * ...
 * N维前缀和：可以理解为D维空间上，区域[0,d1] x [0,d2] x ... x [0,dn]一共存在多少个点
 * 例如 sum[x1][x2][x3][x4] 是四维空间(0,0,0,0) ~ (x1,x2,x3,x4)这个空间内点的数量
 * 如果以几何的角度看多维前缀和 就需要使用容斥定律计算。
 *
 * 计算n维前缀和
 * 可以用dp的思想递推 定义dp[i][s]: 边界点状态s且后n-i维相同的所有点的数量
 * ([0,i]维度可以相同 可以不同)
 * dp[i][s] = dp[i - 1][s] + dp[i][s1]
 * 第1项：dp[i - 1][s]，边界点状态s，且后n-i+1维相同的所有点数量
 * 第i位是相同的，这是dp[i][s]的一个子集
 * 第2项：s1表示第i维比s少1的边界点(s1最小为0)，dp[i][s1]边界点状态s1且后n-i维相同的所有点的数量
 * 第i位是不同的，s要加上前序点的数量
 *
 * 边界条件 dp[0][s]: 边界点状态s 且n维坐标都相同的点的数量，即就是s表示的那一个点的数量
 * 最终答案 dp[n][s]: 边界点状态s 且n维坐标都不相同点点数量
 */

/*
 * n维前缀和 f的下标表示状态 这里假定下标是用每一个十进制数位来表示某一维度坐标
 * 根据题目需要 也可以用任意进制的数位来表示某个维度
 */
/*
 * 运用
 * https://www.luogu.com.cn/problem/AT_arc136_d
 */
vector<int> multiPreSum(vector<int> f, int n) {
    int m = f.size();
    vector<vector<int>> dp(n + 1, vector(m, 0));
    for(int i = 0; i < m; i++)
        dp[0][i] = f[i];
    for(int i = 1; i <= n; i++) {
        int p = pow(10, i - 1);
        for(int s = 0; s < m; s++) {
            dp[i][s] = dp[i - 1][s];
            if((s / p) % 10) dp[i][s] += dp[i][s - p];
        }
    }
    return dp[n];
}

/*
 * 上述方法还可以进行 压缩优化 将第i维度去掉
 */
vector<int> multiPreSum2(vector<int> f, int n) {
    int m = f.size();
    vector<int> dp(m, 0);
    for(int i = 0; i < m; i++)
        dp[i] = f[i];
    for(int i = 1; i <= n; i++) {
        int p = pow(10, i - 1);
        for(int s = 0; s < m; s++)
            if((s / p) % 10) dp[s] += dp[s - p];
    }
    return dp;
}


/**
     * 由二维数组得到二维前缀和
     * 有时候要注意数据范围，前缀和可能需要使用long
     */
vector<vector<ll>> getPreSum(vector<vector<int>>& nums){
    int n = nums.size(), m = nums[0].size();
    vector<vector<ll>> preSum(n + 1, vector(m + 1, 0ll));
    for(int i = 1; i <= n; i++){
        ll lineSum = 0;
        for(int j = 1; j <= m; j++){
            lineSum += nums[i - 1][j - 1];
            preSum[i][j] = preSum[i - 1][j] + lineSum;
        }
    }
    return preSum;
}

/**
 * 根据二维前缀和求原矩形区域上的和
 * 左上角坐标 x1,y1; 右下角坐标 x2,y2
 */
ll sumOf(vector<vector<ll>>& preSum, int x1, int y1, int x2, int y2){
    return preSum[x2 + 1][y2 + 1] - preSum[x1][y2 + 1] - preSum[x2 + 1][y1] + preSum[x1][y1];
}

/*
 * 模意义下的前缀和 类比字符串hash
 */
const int mod = 1e9 + 7;
vector<int> preSum_mod(vector<int> nums) {
    int n = nums.size();
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        ans[i] = (ans[i - 1] * 10 + nums[i - 1]) % mod;
    }
    return ans;
}

int modOf(vector<int>& arr, int l, int r) {

}