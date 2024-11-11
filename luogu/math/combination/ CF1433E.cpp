/**
 * @Time : 2024/7/6-4:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1433E
 */
 /*
  * 两个步骤
  * 先分组 C(n, n / 2) 但是注意两个组之间没有顺序性 因此还要除以2
  * 然后是计算一个组中的不同顺序 找规律
  * 3:2
  * 4:6
  * 5:24
  * 6:120
  * 7:720
  * 8:5040
  * 9:40320
  * 10:362880
  * 发现就是累乘
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 72, mod = 1e9 + 7;
typedef long long ll;
int T, n;

long long factorial(int n)
{
    long long m = 1;
    for (int i = 1; i <= n; i++){
        m *= i;
    }
    return m;
}

long long C(int n, int m) {
    return factorial(n) / (factorial(m) * factorial(n - m));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    ll mul = 1;
    for(int i = 2; i < n / 2; i++)
        mul *= i;
    ll comb = C(n, n / 2);
    cout << comb / 2 * mul * mul << endl;
};