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
const int N = 1e5 + 5, P = 13331;
ll n, a[N], b[N], edges[N][2];

bool solve() {

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> b[i];
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int j = 2, x, k; j <= n; j++) {
        cin >> x >> k;
        edges[j][0] = x, edges[j][1] = k;
    }
    cout << (solve() ? "YES" : "NO") << "\n";
}