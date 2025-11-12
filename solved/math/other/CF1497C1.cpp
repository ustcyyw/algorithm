/**
 * @Time : 2024/3/13-10:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * n为奇数 直接拆分为 1 + 2个相同的偶数（n / 2）
 * 为偶数 那么根据题目输入限制n >= 4
 *  如果(n-2) / 2是偶数，可以拆分为2 + 2个相同的偶数(n-2) / 2, 这三个数的lcm是(n-2) / 2
 *  如果(n-2) / 2是奇数，可以拆分为 n / 2, n / 4, n / 4
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 5e5 + 5;
int T, n, k, cnt[N];

void solve() {
    if(n % 2 == 1 || (n - 2) % 4 == 0) {
        int t = n % 2 == 1 ? 1 : 2;
        cout << t << " ";
        n -= t;
        cout << n / 2 << " " << n / 2 << "\n";
    }
    else cout << n / 2 << " " << n / 4 << " " << n / 4 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        solve();
    }
};