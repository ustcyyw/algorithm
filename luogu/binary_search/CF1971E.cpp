/**
 * @Time : 2025/2/15-11:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1971E 1500 二分查找 sb卡精度题
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
int T, n, k, q;
vector<ll> a, b;

void solve(int d) {
    int idx = lower_bound(a.begin(), a.end(), d) - a.begin();
    if(a[idx] == d) {
        cout << b[idx] << " ";
        return;
    }
    long double t = (d - a[idx - 1]) * (b[idx] - b[idx - 1]) * (long double)1.0 / (a[idx] - a[idx - 1]) + b[idx - 1];
    cout << (int)t << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k >> q;
        a.assign(k + 1, 0), b.assign(k + 1, 0);
        for(int i = 1; i <= k; i++)
            cin >> a[i];
        for(int i = 1; i <= k; i++)
            cin >> b[i];
        for(int i = 1, d; i <= q; i++) {
            cin >> d;
            solve(d);
        }
        cout << "\n";
    }
};