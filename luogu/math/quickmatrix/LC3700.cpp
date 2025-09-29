/**
 * @Time : 2025/9/28-15:39
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3700 2446 动态规划 矩阵快速幂
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

class Solution {
public:

    vector<vector<ll>> matrixMul(vector<vector<ll>>& A, vector<vector<ll>>& B){
        int N = A.size(), M = B[0].size(), K = A[0].size();
        vector<vector<ll>> ans(N, vector(M, 0ll));
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                for(int k = 0; k < K; k++)
                    ans[i][j] = (ans[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
            }
        }
        return ans;
    }

    vector<vector<ll>> quickPower(vector<vector<ll>>& a, ll b){
        int n = a.size(); // 能进行快速幂的矩阵 是一个方阵
        vector<vector<ll>> ans(n, vector(n, 0ll));
        for(int i = 0; i < n; i++)
            ans[i][i] = 1;
        while (b != 0){
            if((b & 1) == 1) ans = matrixMul(ans , a);
            a = matrixMul(a, a);
            b >>= 1;
        }
        return ans;
    }

    int zigZagArrays(int n, int l, int r) {
        int d = r - l + 1;
        vector<vector<ll>> I(d, vector(d, 0ll)), D(d, vector(d, 0ll)), T(1, vector(d, 1ll));
        for(int i = 0; i < d; i++) {
            for(int j = 0; j < i; j++) // 得到后两个元素降序的方案 对应的矩阵
                D[i][j] = 1;
            for(int j = i + 1; j < d; j++) // 得到后两个升序的方案 对应的矩阵
                I[i][j] = 1;
        }
        vector<vector<ll>> A = matrixMul(D, I); // 降序再升序 得到的是升序结尾的方案
        vector<vector<ll>> temp = quickPower(A, (n - 1) / 2);
        if((n - 1) % 2 == 1) temp = matrixMul(temp, D); // 如果序列还剩一个位置 就再乘降序矩阵一次 填充最后一个位置
        temp = matrixMul(T, temp);
        ll ans = 0;
        for(ll num : temp[0])
            ans = (ans + num) % mod;
        return ans * 2 % mod; // 这里乘2是因为 在不考虑中间计算过程的时候 最后两元素是升序还是降序 是完全对称的
    }
};