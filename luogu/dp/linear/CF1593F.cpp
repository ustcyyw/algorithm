/**
 * @Time : 2024/7/15-8:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1593F 动态规划
 */
 /*
  * dp[i][j][m1][m2] = 1: 截止i个数字 红-黑的差值为j 并且红的余数为m1，黑的余数为m2的情况存在
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 42, mod = 1e9 + 7;
typedef long long ll;
int T, n, a, b, base = 40, infos[N][2 * N][N][N][3];
string s, ans;

string solve() {
    int dp[N][2 * N][N][N] = {0};
    dp[0][base + 1][(s[0] - '0') % a][0] = true;
    dp[0][base - 1][0][(s[0] - '0') % b] = true;
    for(int i = 0; i < n - 1; i++) {
        int num = s[i + 1] - '0';
        for(int j = base - i - 1; j <= base + i + 1; j++) {
            for(int m1 = 0; m1 < a; m1++) {
                for(int m2 = 0; m2 < b; m2++) {
                    if(!dp[i][j][m1][m2]) continue;
                    dp[i + 1][j + 1][(m1 * 10 + num) % a][m2] = true; // 染成红色
                    int* arr1 = infos[i + 1][j + 1][(m1 * 10 + num) % a][m2];
                    arr1[0] = j, arr1[1] = m1, arr1[2] = m2;
                    dp[i + 1][j - 1][m1][(m2 * 10 + num) % b] = true;
                    int* arr2 = infos[i + 1][j - 1][m1][(m2 * 10 + num) % b];
                    arr2[0] = j, arr2[1] = m1, arr2[2] = m2;
                }
            }
        }
    }
    // 找到最小颜色差距
    int d = -1;
    for(int i = 0; i < n; i++) {
        if(dp[n - 1][base + i][0][0]) {
            d = base + i;
            break;
        }
        if(dp[n - 1][base - i][0][0]) {
            d = base - i;
        }
    }
    if(d == -1) return "-1";
    ans.assign(n, '.');
    for(int i = n - 1, j = d, m1 = 0, m2 = 0; i >= 0; i--) {
        int pj = infos[i][j][m1][m2][0], pm1 = infos[i][j][m1][m2][1], pm2 = infos[i][j][m1][m2][2];
        if(i == 0) pj = base;
        ans[i] = pj > j ? 'B' : 'R';
        j = pj, m1 = pm1, m2 = pm2;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> a >> b >> s;
        cout << solve() << "\n";
    }
};