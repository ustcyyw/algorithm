/**
 * @Time : 2025/1/23-10:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF14C 1700 数学 计算几何
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e9 + 5, mod = 998244353;
ll T, n, a1, b1, a2, b2, c1, c2;
map<ll, int> points, lens;

bool line() {
    cin >> a1 >> b1 >> a2 >> b2;
    if(a1 != a2 && b1 != b2) return false; // 不平行于坐标轴
    if(a1 == a2) c1++;
    if(b1 == b2) c2++;
    ll k1 = a1 * N + b1, k2 = a2 * N + b2;
    points[k1]++, points[k2]++;
    ll dx = a1 - a2, dy = b1 - b2;
    lens[dx * dx + dy * dy]++;
    return true;
}

bool check() {
    for(int i = 1; i <= 4; i++)
        if(!line()) return false;
    if(c1 != 2 || c2 != 2) return false;
    if(points.size() != 4) return false;
    for(auto& [p, cnt] : points)
        if(cnt != 2) return false;
    if(lens.size() > 2) return false;
    for(auto& [l, cnt] : lens)
        if(cnt % 2 == 1) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cout << (check() ? "YES" : "NO") << "\n";
    }
};