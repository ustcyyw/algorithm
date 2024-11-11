/**
 * @Time : 2024/7/24-10:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1619F 构造 + 贪心
 */
 /*
  * n个人 安排m桌 只能向上和向下取整
  * base = n / m, a = n % m
  * 每一轮 会有a个大组 轮着来呗 大组每组有 （base + 1）人
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k;

void solve() {
    int base = n / m, add = n % m, j1 = 0, j2;
    while(k-- > 0) {
        for(int t = 0; t < add; t++) {
            cout << base + 1 << " ";
            for(int i = 0; i < base + 1; i++, j1 = (j1 + 1) % n)
                cout << j1 + 1 << " ";
            cout << "\n";
        }
        j2 = j1;
        for(int t = 0; t < m - add; t++) {
            cout << base << " ";
            for(int i = 0; i < base; i++, j2 = (j2 + 1) % n) {
                cout << j2 + 1 << " ";
            }
            cout << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        solve();
        cout << "\n";
    }
};