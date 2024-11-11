/**
 * @Time : 2023/12/21-11:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 概率期望
 */

/*
 * 概率期望题先推式子。
 * 当前点数为n，那么当前骰子的点数是1、2、3....6 对应的上一次投到的点数就是n、n/2、n/3 ... n/6
 * 记f(n)为投掷得到n的概率
 * f(n) = 1/6 * f(n) + 1/6 * f(n / 2) + 1/6 * f(n/3) + .. + 1/6 * f(n/6)
 * 5/6 * f(n) =  1/6 * f(n / 2) + 1/6 * f(n/3) + .. + 1/6 * f(n/6)
 * f(n) = 1/5 * (f(n / 2) + f(n/3) + .. + f(n/6))
 * 递归方程就有了
 *
 * 本题涉及除法 还需要计算5的逆元
 */
#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;
long long inv, n;

unordered_map<long long, long long> cache;

long long q_pow(long long a, long long b) {
    long long res = 1;
    while(b) {
        if(1 & b) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long dfs(long long x) {
    if(cache.count(x)) return cache[x];
    long long p = 0;
    for(int i = 2; i <= 6; i++) {
        if(x % i == 0)
            p += dfs(x / i);
    }
    p = p % mod * inv % mod;
    cache[x] = p;
    return p;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    inv = q_pow(5, mod - 2);
    cache[1] = 1;
    cin >> n;
    cout << dfs(n) << endl;
}