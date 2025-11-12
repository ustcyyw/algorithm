/**
 * @Time : 2024/3/20-9:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 4e5 + 5;
ll T, a, b, m;

ll solve() {
    ll c1 = m / a, c2 = m / b;
    return c1 + c2 + 2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> a >> b >> m;
        cout << solve() << "\n";
    }
};