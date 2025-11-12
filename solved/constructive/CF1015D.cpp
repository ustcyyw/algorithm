/**
 * @Time : 2024/4/17-7:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 先尽量多走，走到一定距离后 后续就每一次只走1个距离即可
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305, M = 1e5 + 5;
ll n, k, s;

void solve() {
    ll maxM = n - 1;
    if(maxM * k < s || 1 * k > s) { // 按最大距离走都都不够s和按最小距离走都超过s
        cout << "NO";
        return;
    }
    cout << "YES" << "\n";
    for(int x = 1; k > 0; k--) {
        ll dx = min(s - (k - 1), maxM);
        if(x + dx <= n) x += dx;
        else x -= dx;
        cout << x << " ";
        s -= dx;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> s;
    solve();
};