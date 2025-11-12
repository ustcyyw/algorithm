/**
 * @Time : 2024/11/21-10:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2036F 数学 位运算 异或性质 正难则反 1900 参考部分思路
 */
/*
  * 令f[l,r]表示 自然数[l,r]上所有数的异或
  * f[l,r] = f[0,l-1] xor f[0,r] 因此从形式上看只需要计算f[0,x]
  * 但要求的结果只保留有趣数 要排除无趣数
  * fa[0,x]表示自然数[0,x]中的有趣数异或，fb[0,x]表示自然数[0,x]中的无趣数异或
  * f[0,x] = fa[0,x] xor fb[0,x]
  * 题目要求的答案是 fa[0,x] = f[0,x] xor fb[0,x]
  * （这里直接求不好算 所以反着算fb）
  *
  * 首先计算 f[0,x]
  * 例如 f[0,7]: (0^1) ^ (2^3) ^ (4^5) ^ (6^7)
  * 两两一组 除了最后一位二进制位不同，其它二进制位都相同
  * 因此每一组的结果都是1 只需要考虑有多少组即可 组数为 (x + 1) / 2，判断组数是奇数还是偶数即可
  * 这是x为奇数的情况 而x为偶数时 f[0,x] = f[0,x-1] ^ x, x-1就是奇数
  *
  * 然后计算 fb[0,x]
  * 无趣数分为两个部分 2^p 的更低位 由k确定；第p位及更高位单独拿出来看 也是连续的数
  * 例如 p = 3, mod = 2 ^ 3 = 8, k = 6
  * 6：   000-110
  * 14：  001-110
  * 22：  010-110
  * 30：  011-110
  * 38：  100-110
  * 46：  101-110
  * 前半部分和计算f[0,x]类似 也是分组，看组数的奇偶性
  * 后半部分的计算 就是特定数量的k异或 也需要看奇偶性
  * 所以 应当首先计算[0,x]范围内有多少个无趣数 假定有cnt个
  * k + (cnt - 1) * mod <= x
  * cnt - 1 = (x - k) / mod, 向下取整
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 1000000;
ll T, p, k, l, r;

ll f(ll x) {
    if(x == 0) return 0;
    if(x % 2 == 1) return (x + 1) / 2 % 2;
    return x ^ f(x - 1);
}

ll fb(ll x) {
    ll mod = pow(2ll, p), cnt = x < k ? 0 : (x - k) / mod + 1;
    // 注意计算前缀的时候 有cnt个无趣数 对于前缀部分来说是计算f[0,cnt-1]
    ll prefix = cnt == 0 ? 0 : f(cnt - 1), suffix = cnt % 2 == 1 ? k : 0;
    return (prefix << p) | suffix;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> l >> r >> p >> k;
        ll num1 = f(r) ^ fb(r), num2 = f(l - 1) ^ fb(l - 1);
        cout << (num1 ^ num2) << "\n";
    }
};