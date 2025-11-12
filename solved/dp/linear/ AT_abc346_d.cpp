/**
 * @Time : 2024/3/24-11:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, MOD = 1e9 + 7;
ll T, n, k, c[N];
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    for(int i = 0; i < n; i++)
        cin >> c[i];
    // 第二维坐标1表示已经有一组相同了，0表示还没有一组相同。dp0表示以0结尾
    vector<vector<ll>> dp0(n, vector(2, (ll)1e15)), dp1(n, vector(2, (ll)1e15));
    if(s[0] == '0') dp0[0][0] = 0, dp1[0][0] = c[0];
    else dp0[0][0] = c[0], dp1[0][0] = 0;
    for(int i = 1; i < n; i++) {
        ll c0 = s[i] == '0' ? 0 : c[i], c1 = s[i] == '1' ? 0 : c[i];
        dp0[i][0] = dp1[i - 1][0] + c0; // 当前以0结尾 且没有一组相同
        dp1[i][0] = dp0[i - 1][0] + c1;
        dp0[i][1] = min(dp0[i - 1][0] + c0, dp1[i - 1][1] + c0); // 当前以0结尾 且有一组相同
        dp1[i][1] = min(dp1[i - 1][0] + c1, dp0[i - 1][1] + c1); // 当前以1结尾 且有一组相同
    }
    cout << min(dp0[n - 1][1], dp1[n - 1][1]);
};