/**
 * @Time : 2024/2/15-11:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 要保证峰最大化
  * 对于奇数长度的数组 应该从下标2的位置开始 每间隔1就得造一个山峰 直接计算即可
  * 对于偶数长度的数组 允许有两个山峰之间间隔2（包括边界情况）
  * dp1[i]: 截止i位置且以i为山峰 还没有间隔2的山峰的最小操作次数
  * dp2[i]: 截止i位置且以i为山峰 有一组间隔2的山峰的最小操作次数
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int T, n, h[N];
ll dp1[N], dp2[N];

int ope(int i) {
    int t = max(h[i - 1], h[i + 1]) + 1;
    return h[i] >= t ? 0 : t - h[i];
}

void solve1() {
    ll res = 0;
    for(int i = 2; i <= n; i += 2)
        res += ope(i);
    cout << res << endl;
}

void solve2() {
    fill(dp1, dp1 + n + 1, 1e15), fill(dp2, dp2 + n + 1, 1e15);
    dp1[0] = dp2[0] = 0, dp1[2] = ope(2);
    for(int i = 3; i <= n; i++) {
        int t = ope(i);
        dp1[i] = dp1[i - 2] + t;
        dp2[i] = min(dp1[i - 3], dp2[i - 2]) + t;
    }
    cout << min(min(dp1[n - 2], dp1[n - 1]), dp2[n - 1]) << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> h[i];
        if(n % 2 == 1) solve1();
        else solve2();
    }
};