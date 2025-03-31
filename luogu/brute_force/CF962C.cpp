/**
 * @Time : 2025/3/30-11:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF962C 1400 暴力枚举 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, M = 30;
int num, n;
string s;

bool check(string t) {
    int m = t.size(), i = 0, j = 0;
    while(i < n && j < m) {
        if(s[i] == t[j]) i++, j++;
        else i++;
    }
    return j == m;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> num;
    s = to_string(num), n = s.size();
    for(int i = sqrt(num); i >= 1; i--) {
        string t = to_string(i * i);
        if(check(t)) {
            cout << n - t.size();
            return 0;
        }
    }
    cout << -1;
}