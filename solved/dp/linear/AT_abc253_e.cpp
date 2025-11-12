/**
 * @Time : 2023/8/16-9:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1006, M = 5005, mod = 998244353;
int n, m, k;
long sum[N][M] = {0};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++)
        sum[0][i] = sum[0][i - 1] + 1;
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= m; j++) {
            int l = max(j - k, 0), r = min(j + k, m + 1);
            long t = sum[i - 1][l] + sum[i - 1][m] - sum[i - 1][r - 1];
            if(k == 0) t -= sum[i - 1][j] - sum[i - 1][j - 1];
            sum[i][j] = (sum[i][j - 1] + t + mod) % mod;
        }
    }
    cout << sum[n - 1][m] << endl;
}