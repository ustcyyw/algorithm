/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 令f[l,r]表示 自然数[l,r]上所有数的异或
  * f[l,r] = f[0,l-1] xor f[0,r] 因此从形式上看只需要计算f[0,x]
  * 但要求的结果只保留有趣数 要排除无趣数
  * fa[0,x]表示自然数[0,x]中的有趣数，fb[0,x]表示自然数[0,x]中的无趣数
  * f[0,x] = fa[0,x] xor fb[0,x]
  * 题目要求的答案是 fa[0,x] = f[0,x] xor fb[0,x]
  *
  * 首先计算 f[0,x]
  * 例如 f[0,7]: (0^1) ^ (2^3) ^ (4^5) ^ (6^7)
  * 两两一组 除了最后一位二进制位不同，其它二进制位都相同
  * 因此每一组的结果都是1 只需要考虑有多少组即可 组数为 (x + 1) / 2，判断组数是奇数还是偶数即可
  * 这是x为奇数的情况 而x为偶数时 f[0,x] = f[0,x-1] ^ x, x-1就是奇数
  *
  * 然后计算 fb[0,x]
  *
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 1000000;
int T, p, k;
ll l, r;

string to_bit_string(ll num) {
    string s;
    while(num > 0) {
        if(num & 1) s.push_back('1');
        else s.push_back('0');
        num >>= 1;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> l >> r >> p >> k;
        ll num1 = cal(r), num2 = cal(l - 1);
        cout << (num1 ^ num2) << "\n";
    }
};