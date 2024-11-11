/**
 * @Time : 2024/3/20-9:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 3e5 + 5;
int T, n, lc[N], rc[N];
string s;

ll solve() {
    memset(lc, 0, sizeof(lc)), memset(rc, 0, sizeof(rc));
    for(int i = 1; i <= n; i++)
        lc[i] = lc[i - 1] + (s[i] == '0');
    for(int i = n; i >= 0; i--)
        rc[i] = rc[i + 1] + (s[i] == '1');
    int ans = -1;
    double dis = 1e9;
    for(int i = 0; i <= n; i++) {
        int c1 = lc[i], c2 = rc[i + 1];
        if(c1 >= (i + 1) / 2 && c2 >= (n - i + 1) / 2) {
            double dt = abs(n * 1.0 / 2 - i);
            if(dt < dis) {
                ans = i;
                dis = dt;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cin >> s;
        s = "." + s;
        cout << solve() << "\n";
    }
};