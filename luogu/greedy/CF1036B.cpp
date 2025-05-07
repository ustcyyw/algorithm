/**
 * @Time : 2025/5/6-10:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1036B 1600 贪心 分类讨论
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5, mod = 998244353;
ll T, n, m, k;

ll solve() {
    if(n > m) swap(n, m);
    if(k < m) return -1;
    ll diff = m - n, left = k - n;
    if(diff % 2 == 0) {
        if(left % 2 == 0) return k;
        else return k - 2;
    } else return k - 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> k;
        cout << solve() << "\n";
    }
}