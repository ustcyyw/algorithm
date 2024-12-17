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
const int N = 1e5 + 5;
int T, n, a[N], b[N];

int dfs(int a, int b) {
    if(a == 0) return 0;
    if(b == 0) return 1;
    if(a <= b) return 2 + dfs(b - a, a);
    int c = a / b;
    if(c == 1) return 1 + dfs(b, a - b);
    if(c % 2 == 0) {
        int t = dfs(a % b, b);
        return c / 2 * 3 + t;
    }
    else {
        int t = dfs(a % b + b, b);
        return (c - 1) / 2 * 3 + t;
    }
}

bool solve() {
    for(int i =1, pre = -1; i <= n; i++) {
        if(a[i] == 0 && b[i] == 0) continue;
        int c = dfs(a[i], b[i]), mod = c % 3;
        if(pre == -1) pre = mod;
        else if(pre != mod) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};