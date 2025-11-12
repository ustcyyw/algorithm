/**
 * @Time : 2024/7/23-7:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1618E 构造 数学
 */
 /*
  * 找规律 发现b的相邻项相减有规律
  * b的所有项相加 系数是可以提取的
  * 于是可以进行解方程
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 4e4 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, b[N], ans[N];

bool solve() {
    ll sum = accumulate(b + 1, b + n + 1, 0ll), cc = n * (n + 1) / 2;
    if(sum % cc != 0) return false;
    ll base = sum / cc;
    for(int i = 2; i <= n; i++) {
        ll temp = base - (b[i] - b[i - 1]);
        if(temp % n != 0 || temp / n < 1) return false;
        ans[i] = temp / n;
    }
    ll temp = base - (b[1] - b[n]);
    if(temp % n != 0 || temp / n < 1) return false;
    ans[1] = temp / n;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        if(!solve()) cout << "NO\n";
        else {
            cout << "YES\n";
            for(int i = 1; i <= n; i++)
                cout << ans[i] << " ";
            cout << "\n";
        }
    }
};