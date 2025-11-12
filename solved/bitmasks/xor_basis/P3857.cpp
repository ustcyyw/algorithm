/**
 * @Time : 2025/3/17-7:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P3857 线性基
 */
 /*
  * 某个开关按两次 等于这个开关没有按
  * 因此最终能得到多少个灯状态 其实就是转化为选择一些开关（可以一个都不选）
  * 选出来的开关按一次即可
  * 对于某一个灯 会有多个选出来的开关控制它 都按一次 就看是奇数个还是偶数个
  * 这些行为和异或一致
  * 因此灯的状态就是选出的开关的异或值 要从集合a中选出一些元素得到其异或值 问有多少个异或值
  * 就是求线性基 然后求总共可以表示出多少个异或值 本题是允许灯全灭的
  */
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, M = 50;
ll T, n, m, basis[M + 1];
string s;

bool insert(ll num) {
    for(int i = M; i >= 0; i--) {
        if(num >> i == 1) {
            if(basis[i] == 0) {
                basis[i] = num;
                return true;
            } else num ^= basis[i];
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        int cnt = 0;
        for(int i = 0; i < m; i++) {
            cin >> s;
            ll num = 0;
            for(ll j = 0; j < s.size(); j++) {
                if(s[j] == 'O')
                    num |= 1ll << j;
            }
            cnt += insert(num);
        }
        cout << (ll)pow(2ll, cnt) % 2008;
    }
}