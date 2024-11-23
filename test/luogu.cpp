/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, sum[N];
string s1, s2;

void solve() {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        cin >> s1 >> s2;
        s1 = '.' + s1, s2 = '.' + s2;
        solve();
    }
};