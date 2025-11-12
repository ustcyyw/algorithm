/**
 * @Time : 2024/5/17-10:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1203E 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 150005, D = 1e9;
int T, n, m, a[N], b[N];

void solve() {
    for(int i = 150000; i >= 1; i--) {
        if(a[i] == 0) continue;
        if(b[i + 1] + a[i + 1] == 0) b[i + 1] = 1, a[i]--;
        if(a[i] + b[i] >= 2 && a[i] > 0) b[i - 1]++, a[i]--;
    }
    int cnt = 0;
    for(int i = 1; i < N; i++)
        if(a[i] + b[i] > 0) cnt++;
    cout << cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        a[num]++;
    }
    solve();
};