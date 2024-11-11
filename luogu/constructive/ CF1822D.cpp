/**
 * @Time : 2024/5/28-9:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1822D 构造
 */
/*
  * 1.n只能放在开头 因为n不放在第一项的话 n的前一项和n所在这项的前缀和 % n后相等
  * sum_pre % n = (sum_pre + n) % n
  * 2.在1的基础上发现 n * (n + 1) / 2 % mod = 0
  * 那么一定无解 因为所有数之和 %n 后为0，而n放在开头取模后也是0 就出现了重复了
  *
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        if(n == 1) cout << "1\n";
        else if(n * (n + 1) / 2 % n == 0) {
            cout << -1 << "\n";
        } else {
            cout << n << " ";
            for(int i = 1; i <= n - 3; i += 2) {
                int a = i, b = n + - 1 - i;
                cout << a << " " << b << " ";
            }
            cout << n - 1 << "\n";
        }
    }
};