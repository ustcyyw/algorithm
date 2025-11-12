/**
 * @Time : 2023/12/8-8:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 每个物品的放置是独立的 并且可以放置1到m个
 * 从m个包选1个、2个...n个来放置 一共有 t = C(m,1) + C(m,2) + ... + C(m,n) = 2 ^ m - 1种方式
 * 有n种物品 因此一共有 t ^ n 种方式
 * 还需要使用快速幂
 */
#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

long long qPow(long long a, int b) {
    long long res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    int n, m;
    cin >> n >> m;
    long long t = (qPow(2, m) - 1 + mod) % mod;
    cout << qPow(t, n) << endl;
}