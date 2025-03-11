/**
 * @Time : 2025/3/10-8:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF863D 1800 正难则反 模拟
 */
 /*
  * 倒着计算 bi 这个索引一开始来源于哪个位置的数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, P = 13331;
int n, q, m, b[105], a[N], ope[N][3];

int cal(int idx, int i) {
    if(i == 0) return a[idx];
    int t = ope[i][0], l = ope[i][1], r = ope[i][2];
    if(idx < l || idx > r) return cal(idx, i - 1);
    int ni;
    if(t == 1) ni = idx != l ? idx - 1 : r;
    else ni = l + r - idx;
    return cal(ni, i - 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> q >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= q; i++)
        cin >> ope[i][0] >> ope[i][1] >> ope[i][2];
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
        cout << cal(b[i], q) << " ";
    }
}