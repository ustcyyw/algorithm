/**
 * @Time : 2025/3/12-8:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF873C 1600 贪心 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 105, P = 13331;
int n, m, k, sum[N][N], matrix[N][N], ans = 0, ope = 0;

void init_sum(int j) {
    for(int i = 1; i <= n; i++) {
        sum[j][i] = sum[j][i - 1] + matrix[i][j];
    }
}

void cal(int j) {
    int at = 0, ot = 0;
    for(int i = n; i >= 1; i--) {
        if(matrix[i][j] == 0) continue;
        int hi = min(i + k - 1, n), temp = sum[j][hi] - sum[j][i - 1];
        if(temp >= at)
            at = temp, ot = sum[j][i - 1];
    }
    ans += at, ope += ot;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++)
            cin >> matrix[i][j];
    }
    for(int j = 1; j <= m; j++) {
        init_sum(j);
        cal(j);
    }
    cout << ans << " " << ope << "\n";
}