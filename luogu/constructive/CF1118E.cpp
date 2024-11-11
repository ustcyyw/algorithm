/**
 * @Time : 2024/5/6-10:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll n, k;

void solve() {
    for(int i = 1, cnt = 0; i < k && cnt < n; i++) {
        for(int j = i + 1; j <= k; j++) {
            cout << i << " " << j << "\n";
            if(++cnt >= n) break;
            cout << j << " " << i << "\n";
            if(++cnt >= n) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    if(n > k * (k - 1)) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << "\n";
    solve();
};