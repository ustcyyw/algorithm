/**
 * @Time : 2024/12/11-4:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1926E 1500 数学 数论
 */
/*
 * 第一行放所有奇数，那么任何奇数倍得出的数（奇数*奇数=奇数） 都已经在第一行中出现了
 * 所有后续只需要考虑偶数倍的行
 * 2倍的行 都没出现过 都可选
 * 4倍的行 从因式的角度来看 是奇数 * 2 * 2 都可选
 * 6倍的行 是 奇数 * 3 * 2 = 奇数 * 2 已经在2这行出现过了
 * 8倍的行 是奇数 * 2 * 2 * 2都可选
 * 10倍的行 是奇数 * 5 * 2 = 奇数 * 2 已经在2这行出现过了
 * 因此只有2的幂次的倍数会出现新数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k;

int solve() {
    for(int i = 1, temp = 1; i < 31; i++, temp *= 2) {
        ll lo = 1, hi = n; // 二分找这一行总共有多少个数
        while(lo < hi) {
            ll mid = (lo + hi + 1) >> 1;
            ll base = mid * 2 - 1;
            if(base * temp > n) hi = mid - 1;
            else lo = mid;
        }
        if(k > lo) k -= lo;
        else return (k * 2 - 1) * temp;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        cout << solve() << "\n";
    }
};