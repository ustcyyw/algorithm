/**
 * @Time : 2024/4/11-10:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 1: 001
  * 2: 010
  * 3: 011
  * 4: 100
  * 4比较特殊 它单独占了一个二进制位 与 1 2 3 不会相互影响
  * 4如果是奇数个 一定要先拿掉一个 确保4出现偶数次
  * 可以最后再来移走4
  *
  * 考虑1 2 3，并且3个数最多有200个，可以dp
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 205;
int T, p1, p2, p3, p4, dp[N][N][N];

int init = []() -> int {
    for(int i = 0; i <= 200; i++) {
        int b1 = i % 2 == 0 ? 0 : 1;
        for(int j = 0; j <= 200; j++) {
            int b2 = j % 2 == 0 ? 0 : 2;
            for(int k = 0; k <= 200; k++) {
                if(i + j + k == 0) continue;
                int b3 = k % 2 == 0 ? 0 : 3;
                dp[i][j][k] = 0;
                if(i - 1 >= 0) dp[i][j][k] = dp[i - 1][j][k];
                if(j - 1 >= 0) dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k]);
                if(k - 1 >= 0) dp[i][j][k] = max(dp[i][j][k], dp[i][j][k - 1]);
                dp[i][j][k] += (b1 ^ b2 ^ b3) == 0;
            }
        }
    }
    return 0;
}();

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> p1 >> p2 >> p3 >> p4;
        cout << (p4 / 2 + dp[p1][p2][p3]) << "\n";
    }
};