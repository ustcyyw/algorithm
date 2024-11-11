/**
 * @Time : 2024/5/24-11:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : k进制下的高精度加法
 */
 /*
  * 模版题 luogu p1601
  * https://www.luogu.com.cn/problem/P1601
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, a[N], b[N], c[N], k = 10;
string s1, s2;

void reverse(string& s, int* arr) {
    int m = s.size();
    for(int i = 0; i < m; i++)
        arr[i] = s[m - 1 - i] - '0';
}

void add() {
    reverse(s1, a), reverse(s2, b);
    n = max(s1.size(), s2.size());
    for(int i = 0; i <= n; i++) {
        c[i] += a[i] + b[i];
        c[i + 1] = c[i] / k; // 进位
        c[i] %= k;
    }
    int i = n;
    while(i > 0 && c[i] == 0) i--;
    for(; i >= 0; i--)
        cout << c[i];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> n;
    cin >> s1 >> s2;
    add();
};