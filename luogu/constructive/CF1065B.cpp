/**
 * @Time : 2025/5/3-10:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1065B 1300 构造 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, m;

ll min_val() {
    if(m * 2 >= n) return 0;
    return n - 2 * m;
}

ll max_val() {
    for(ll i = 0; i <= n; i++) {
        if(i * (i - 1) / 2 >= m)
            return n - i;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    cout << min_val() << " " << max_val();
}