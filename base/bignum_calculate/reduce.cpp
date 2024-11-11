/**
 * @Time : 2024/5/24-4:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : k进制下的高精度减法
 */
 /*
  * 模板题 P2142
  * https://www.luogu.com.cn/problem/P2142
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 10500;
int n, a[N], b[N], c[N], k = 10;
string s1, s2;

bool lessThan(string& s1, string& s2) {
    int m1 = s1.size(), m2 = s2.size();
    if(m1 < m2) return true;
    if(m1 > m2) return false;
    for(int i = 0; i < m1; i++) {
        if(s1[i] < s2[i]) return true;
        else if(s1[i] > s2[i]) return false;
    }
    return false;
}

void reverse(string& s, int* arr) {
    int m = s.size();
    for(int i = 0; i < m; i++)
        arr[i] = s[m - 1 - i] - '0';
}

void reduce() {
    string sign;
    if(lessThan(s1, s2)) {
        sign = "-";
        swap(s1, s2);
    }
    reverse(s1, a), reverse(s2, b);
    n = max(s1.size(), s2.size());
    for(int i = 0; i <= n; i++) {
        if(a[i] < b[i]) a[i + 1]--, a[i] += k; // 向高位借
        c[i] = a[i] - b[i];
    }
    int i = n;
    while(i > 0 && c[i] == 0) i--; // 去除前导0
    cout << sign;
    for(; i >= 0; i--)
        cout << c[i];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> n;
    cin >> s1 >> s2;
    reduce();
};