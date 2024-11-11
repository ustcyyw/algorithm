/**
 * @Time : 2024/5/24-4:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : k进制下的高精度乘法
 */
 /*
  * 模板题 P1303
  * https://www.luogu.com.cn/problem/P1303
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 4e6 + 5;
int n, a[N], b[N], c[N], k = 10;
string s1, s2;

void reverse(string& s, int* arr) {
    int m = s.size();
    for(int i = 0; i < m; i++)
        arr[i] = s[m - 1 - i] - '0';
}

void mul() {
    reverse(s1, a), reverse(s2, b);
    int m1 = s1.size(), m2 = s2.size();
    for(int i = 0; i < m1; i++) {
        for(int j = 0; j < m2; j++) {
            c[i + j] += a[i] * b[j];
            c[i + j + 1] += c[i + j] / k;
            c[i + j] %= k;
        }
    }
    int i = m1 + m2;
    while(i > 0 && c[i] == 0) i--; // 去除前导0
    for(; i >= 0; i--)
        cout << c[i];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> n;
    cin >> s1 >> s2;
    mul();
};