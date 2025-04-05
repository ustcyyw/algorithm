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
typedef long double ld;
const int N = 1e6 + 15, M = 30;
int n;

bool check() {
    int x1, y1, x2, y2, x, y;
    cin >> x1 >> y1 >> x2 >> y2 >> x >> y;
    int dx = abs(x1 - x2), dy = abs(y1 - y2);
    if(dx % x != 0 || dy % y != 0) return false;
    int cx = dx / x, cy = dy / y;
    return cx % 2 == cy % 2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cout << (check() ? "YES" : "NO");
}