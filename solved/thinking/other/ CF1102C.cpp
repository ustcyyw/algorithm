/**
 * @Time : 2024/4/26-5:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1102C
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5005, mod = 998244353;
int n, x, y;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> x >> y;
    if(x > y) {
        cout << n;
        return 0;
    }
    int cnt = 0;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        if(num <= x) cnt++;
    }
    cout << (cnt + 1) / 2;
};