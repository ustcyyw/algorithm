/**
 * @Time : 2025/3/5-8:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF846F 1800 贡献法 数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, P = 13331;
ll n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    ll total = 0;
    map<int, int> pre;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        ll left = i - pre[num], right = n - i + 1;
        total += left * right * 2 - 1;
        pre[num] = i;
    }
    cout << total * 1.0 / n / n;
}