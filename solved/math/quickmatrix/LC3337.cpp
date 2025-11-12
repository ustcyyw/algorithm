/**
 * @Time : 2024/12/5-2:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3337 矩阵快速幂
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;

class Solution {
public:
    vector<vector<ll>> matrixMul(vector<vector<ll>>& A, vector<vector<ll>>& B){
        int N = A.size(), M = B[0].size(), K = A[0].size();
        vector<vector<ll>> ans(N, vector(M, 0ll));
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                for(int k = 0; k < K; k++)
                    ans[i][j] = (int)(((long)ans[i][j] + (A[i][k] * B[k][j])) % mod);
            }
        }
        return ans;
    }
    vector<vector<ll>> quickPower(vector<vector<ll>>& a, int b){
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

    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        vector<vector<ll>> cnt(1, vector(26, 0ll));
        for(char c : s)
            cnt[0][c - 'a']++;
        vector<vector<ll>> matrix(26, vector(26, 0ll));
        for(int i = 0; i < 26; i++) {
            for(int j = (i + 1) % 26, k = 0; k < nums[i]; j = (j + 1) % 26, k++)
                matrix[i][j] = 1;
        }
        matrix = quickPower(matrix, t);
        cnt = matrixMul(cnt, matrix);
        ll ans = 0;
        for(int i = 0; i < 26; i++)
            ans = (ans + cnt[0][i]) % mod;
        return ans;
    }
};