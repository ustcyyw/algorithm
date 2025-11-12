/**
 * @Time : 2025/2/17-10:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF691E 1900 动态规划 数学 矩阵快速幂 看了一眼提示
 */
 /*
  * 如果k比较小 容易想到 dp[i][j]：以nums[j]为结尾 并且长度为i的序列的方案数
  * 并且初状态就是 dp[1][j] = 1
  * 状态转移 dp[i][j] = sum{dp[i - 1][k]}, if (k,j) 满足要求
  * 但是k很大 直接算会超时
  * 当前状态是前一个位置的状态，所有满足要求的k转移而来 将系数视为1
  * 而不满足要求的k，将系数视为0 这样 dp[i][j] = sum{ck * dp[i-1][k]}
  * 于是状态转移可以写成矩阵的形式
  * dp[i-1] * A = dp[i]
  * 其中dp[i]是一个1 * n的矩阵，A是n * n的系数矩阵
  * 因此可以用矩阵快速幂加速计算
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 100 + 5, M = 3e6 + 5, mod = 1e9 + 7;
ll T, n, k, nums[N];

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

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> k;
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        vector<vector<ll>> b(1, vector(n, 1ll));
        vector<vector<ll>> a(n, vector(n, 0ll));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                ll num = nums[i] ^ nums[j];
                if(__builtin_popcountll(num) % 3 == 0) {
                    a[j][i] = 1;
                }
            }
        }
        vector<vector<ll>> A = quickPower(a, k - 1);
        vector<vector<ll>> temp = matrixMul(b, A);
        ll ans = 0;
        for(int i = 0; i < n; i++)
            ans = (ans + temp[0][i]) % mod;
        cout << ans << "\n";
    }
};