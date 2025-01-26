/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 205, mod = 998244353;
int T, n, pos[6];

ll get_len(int x1, int y1, int x2 ,int y2) {
    ll dx = x1 - x2, dy = y1 - y2;
    return dx * dx + dy * dy;
}

bool check(int x1, int y1, int x2, int y2, int x3, int y3) {
    ll l1 = get_len(x1, y1, x2, y2);
    ll l2 = get_len(x1, y1, x3, y3);
    ll l3 = get_len(x2, y2, x3, y3);
    return l1 && l2 && l3 && (l1 == l2 + l3 || l2 == l1 + l3 || l3 == l1 + l2);
}

bool check2(int i, int sign) {
    pos[i] += sign;
    if(check(pos[0], pos[1], pos[2], pos[3], pos[4], pos[5]))
        return true;
    pos[i] -= sign;
    return false;
}

string solve() {
    if(check(pos[0], pos[1], pos[2], pos[3], pos[4], pos[5])) return "RIGHT";
    for(int i = 0; i < 6; i++) {
        if(check2(i, 1) || check2(i, -1)) return "ALMOST";
    }
    return "NEITHER";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        for(int i = 0; i < 6; i++)
            cin >> pos[i];
        cout << solve();
    }
};