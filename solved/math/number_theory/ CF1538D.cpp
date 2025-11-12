/**
 * @Time : 2024/7/11-11:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1538D
 */
/*
 * 计算两数相等的最小操作和最大操作
 * 1.两个数相等的小操作 如果a = b, 0次操作
 * 如果a != b 但是a是b的因子或者b是a的因子 1次操作
 * 如果上述还不成立 那就将两个数都变为1 一同两次操作
 * 2.最大操作次数 就是每次a和b都除以质因子 计算a和b的质因子个数再求和
 *
 * k处于最大操作次数和最小操作次数之间时 总是可以通过k次操作 将两个数都变为1
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, a, b, k;

int count_prime(int num) {
    int cnt = 0;
    for (int i = 2; i * i <= num; i++) {
        while (num % i == 0) {
            num /= i, cnt++;
        }
    }
    if (num != 1) cnt++;
    return cnt;
}

bool check() {
    if(a == b && k == 1) return false;
    if (k > log2(a) + log2(b)) return false;
    int lo = 2;
    if(a == b) lo = 0;
    else if(a % b == 0 || b % a == 0) lo = 1;
    int hi = count_prime(a) + count_prime(b);
    return lo <= k && k <= hi;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> a >> b >> k;
        cout << (check() ? "YES" : "NO") << "\n";
    }
};