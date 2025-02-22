/**
 * @Time : 2025/2/21-3:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1316C 1800 数学 猜结论
 */
/*
  * 将已知的条件联系在一起
  * 1. p是个质数
  * 2. gcd(a0,a1...an) = 1，gcd(b0,b1...bm) = 1
  * gcd(a0,a1...an) = 1说明a序列中的所有数 不存在公共因子
  * p一定不是a序列的公共因子，a序列中至少有一个数不能被p整除
  * 第一个不能被p整除的系数记为ai
  * 同理b序列中第一个不能被p整除的系数记为bj
  * 并且p是一个质数，ai不含p因子，bj也不含p因子，那么ai * aj也一定凑不出p因子
  * 有 ai * bj不能被p整除，那么考虑系数c[i+j]
  * c[i+j] = a0 * b[i+j] + a1 * b[i+j-1] + .. a[i-1] * b[j+1]
  * + ai * bj + a[i+1] * b[j-1] + ... + a[i+j-1] * b1 + a[i+j] * b0
  * 这里假设了有足够多的系数来凑出完整表达式，如果没有 就让那些 a,b 系数为0即可
  * 除了ai * bj项外，任何一项都函数 a[0,i-1]或者b[0,j-1]
  * 这些系数都能被p整除，因此 c[i+j] % p 后 这些项都为0
  * c[i+j] % p = (ai * bj) % p
  * 所以c[i+j]不会被p整除，答案就是i+j
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5;
ll n, m, p;

int find(int total) {
    int idx = -1;
    for(int i = 0, num; i < total; i++) {
        cin >> num;
        if(num % p != 0 && idx == -1) idx = i;
    }
    return idx;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> m >> p;
    cout << find(n) + find(m);
};