/**
 * @Time : 2024/4/2-8:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 50, B = 2e5 + 5;
int T, n;
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    cin >> n;
    for(int i = 0, l, r, k; i < n; i++) {
        cin >> l >> r >> k;
        int len = r - l + 1;
        k %= len;
        l--, r--;
        string t = s;
        for(int j = l; j <= r; j++)
            s[l + (j - l + k) % len] = t[j];
    }
    cout << s;
};