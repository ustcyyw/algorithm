/**
 * @Time : 2023/2/14-9:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 靠全局缓存才通过的 n^3的解法
 *
 * 棍子的绝对高度没有意义，只有相对高度有意义
 * 在n个棍子中考虑看到k个棍子，设一共有 cache[n][k]中排列方式
 * 最高的一根 称为h 一定能被看见
 *
 * 如果有i根棍子放在h的后面，共有C(n - 1, i)个取法。（就是n-1根矮一些的棍子选i根放h后面）
 * 在h后面的i根怎么排都不影响可见性，因此可以全排列A(i,i)
 * 并且还剩下 n - i - 1根棍子放在h前面，他们要可以被看见k-1根，排列方式为 cache[n - i - 1][k - 1]
 * 因此，取i根棍子放h后面的排列方案数为 cache[n - i - 1][k - 1] * C(n - 1, i) * A(i,i)，
 * i的取法则是 i = 0, 1, 2... 直到 k - 1 == n - 1 - i， i == n - k
 *
 * 对i的所有取值求和，就是n个棍子中考虑看到k个棍子的方案数
 */
//int mod = 1e9 + 7, N = 1010;
//vector<long> A;
//vector<vector<long>> cache, C;
//int init = []() {
//    cache = vector(N, vector(N, -1l));
//    A = vector(N, 1l);
//    for(int i = 1; i < A.size(); i++)
//        A[i] = (A[i - 1] * i) % mod;
//    C = vector(N, vector(N, 0l));
//    for (int i = 0; i < N; i++) {
//        C[i][0] = 1;
//        for (int j = 1; j <= i; j++)
//            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
//    }
//    return 0;
//}();
//class Solution {
//public:
//
//    int rearrangeSticks(int n, int k) {
//        if(k == 1) return A[n - 1];
//        if(cache[n][k] != -1) return cache[n][k];
//        long res = 0;
//        for(int i = 0; i < n && n - i >= k; i++){
//            long t = rearrangeSticks(n - i - 1, k - 1);
//            res = (t * A[i] % mod * C[n - 1][i] + res) % mod;
//        }
//        cache[n][k] = res;
//        return res;
//    }
//};


/*
     * 棍子的绝对高度没有意义，只有相对高度有意义
     *
     * dp[i][j]: 使用高度排名前i的棍子，能看见j根的方案数
     * 一般都会想到i根棍子的状态从i-1根转移过来
     * 最高的棍子一定能被看到
     * 1.如果最高的棍子放在最后，那么前i-1根棍子需要被看到j-1根，加上放在最后的最高的棍子，能被看到j根
     * 2.最高的棍子没有放在最后，那么最后一个位置无论放哪一根(共i - 1根)，都不会看到
     * 假设放到最后一个位置的棍子高度为x，那么前面放的棍子就是 (1,2,..,x-1,x+1,...i)
     * (1,2,..,x-1,x+1,...i)这组棍子，应该被看见j根
     *
     * 状态中只强调高度排名前i，每一根棍子多高无所谓，因此(1,2,..,x-1,x+1,...i)这组棍子单独拿出来排
     * 就是将高度排名前i-1的棍子排列，并且能被看见j根 其方案数就是 dp[i - 1][j]
     *
     * 这里的x可以取除最高棍子以外的所有棍子，共(i-1)种取法，每一种取法下，剩余i-1根棍子能看见j根的排列方式都是dp[i - 1][j]
     */
int MOD = 1e9 + 7, N = 1005;
vector<vector<long>> dp(N, vector(N, 0l));
int init = []() {
    dp[0][0] = 1; // 0根棍子可以看见0根的方案数 1种 就是啥也没
    for(int i = 1; i < N; i++){
        for(int j = 1; j <= i; j++){
            dp[i][j] = (dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j]) % MOD;
        }
    }
    return 0;
}();
class Solution {
public:
    int rearrangeSticks(int n, int k) {
        return dp[n][k];
    }
};

int main(){
    Solution s;
    s.rearrangeSticks(3,2);
    cout << 0 << endl;
}