/**
 * @Time : 2024/12/6-9:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2050D 1351 排序 贪心
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n;
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> s;
        for(int i = 1, n = s.size(); i < n; i++) {
            for(int j = i; j > 0 && s[j] - s[j - 1] > 1; j--) {
                swap(s[j], s[j - 1]);
                s[j - 1] = (char)(s[j - 1] - 1);
            }
        }
        cout << s << "\n";
    };
};