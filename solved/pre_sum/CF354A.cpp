/**
 * @Time : 2024/1/25-10:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 假设有6个数 l表示从左边弹出一个数 r表示从右边弹出一个数
 * 完全从一个方向取数 llllll 或者 rrrrrr
 * 交替取数一次 lr-llll 或者 rl-rrrr
 * 交替取数两次 lrlr-ll 或者 rlrl-rr
 *
 * 确定间隔取数的情况下 无论先取那一端 无附加值的部分都一致
 * 区别在于连续的部分 要从左边连续取（交替阶段先l） 还是右边连续取（交替阶段先r）
 * 枚举交替次数 i 属于[0, n/2]，用前缀和计算从左边、右边取的数成本之和 再计算连续取数的额外成本
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
long long n, l, r, ql, qr, nums[N], ls[N], rs[N];

void solve() {
    for(int i = 1; i <= n; i++) {
        ls[i] = ls[i - 1] + nums[i - 1] * l;
        rs[i] = rs[i - 1] + nums[i - 1] * r;
    }
    long long res = LONG_LONG_MAX;
    for(int i = 0; i <= n / 2; i++) {
        long long cnt = n - 2 * i - 1 > 0 ? n - 2 * i - 1 : 0;
        long long t1 = ls[n - i] + rs[n] - rs[n - i] + cnt * ql; // 交替之后 从左边连续取
        long long t2 = ls[i] + rs[n] - rs[i] + cnt * qr; // 交替之后 从右边连续取
        res = min(res, min(t1, t2));
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> l >> r >> ql >> qr;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    solve();
}