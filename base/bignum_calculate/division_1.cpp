/**
 * @Time : 2024/5/24-5:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : k进制下的高精度除法 被除数是简单数
 */
 /*
  * 模版题 P1480
  * https://www.luogu.com.cn/problem/P1480
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 4e6 + 5;
typedef long long ll;
int n, a[N], b, c[N], k = 10;
string s1;

void division() {
    int m1 = s1.size();
    for(int i = 0; i < m1; i++)
        a[i] = s1[i] - '0';
    ll x = 0;
    for(int i = 0; i < m1; i++) {
        c[i] = (k * x + a[i]) / b;
        x = (k * x + a[i]) % b;
    }
    int i = 0;
    while(i < m1 - 1 && c[i] == 0) i++; // 去除前导0
    for(; i < m1; i++)
        cout << c[i];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> n;
    cin >> s1 >> b;
    division();
};