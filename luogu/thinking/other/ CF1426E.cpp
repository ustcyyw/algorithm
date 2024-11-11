/**
 * @Time : 2024/7/4-10:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1426E 思维题 结论题
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, a[3], b[3];

void solve() {
    // 赢得最多 那么就让a尽可能的赢即可 对战他一定能赢的
    int win2 = min(a[0], b[1]) + min(a[1], b[2]) + min(a[2], b[0]);
    // 赢得最少 换句话说就是平局和输 最多 同理 对战他一定会输或者平的局
    int lose = min(a[0], b[2] + b[0]) + min(a[1], b[0] + b[1]) + min(a[2], b[1] + b[2]);
    cout << n - lose << " " << win2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> a[0] >> a[1] >> a[2] >> b[0] >> b[1] >> b[2];
    solve();
};