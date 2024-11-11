/**
 * @Time : 2024/4/16-8:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 5005, M = 1e5 + 5;
int n, k, sum[N] = {0};

void solve() {
    double ans = -1;
    for(int len = k; len <= n; len++) {
        for(int lo = 1; lo + len - 1 <= n; lo++) {
            int temp = sum[lo + len - 1] - sum[lo - 1];
            ans = max(ans, 1.0 * temp / len);
        }
    }
    printf("%7f", ans);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        sum[i] = sum[i - 1] + num;
    }
    solve();
};