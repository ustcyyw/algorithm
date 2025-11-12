/**
 * @Time : 2025/2/21-10:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF797E 2000 根号分治
 */
/*
 * k < 4e2
 * p = p + a[p] + k 动态规划预处理
 *
 * k > 4e2 直接计算 最多跳 1e5/4e2 = 250 次
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, M = 400;
int n, q, a[N], dp[N][M];

void init(int k) {
    for(int i = n; i >= 1; i--) {
        if(i + a[i] + k > n) dp[i][k] = 1;
        else dp[i][k] = dp[i + a[i] + k][k] + 1;
    }
}

int cal(int p, int k) {
    int cnt = 0;
    while(p <= n) {
        p += a[p] + k, cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int ck = 1; ck < M; ck++)
        init(ck);
    cin >> q;
    for(int i = 1, p, k; i <= q; i++) {
        cin >> p >> k;
        if(k < M) cout << dp[p][k] << "\n";
        else cout << cal(p, k) << "\n";
    }
};