/**
 * @Time : 2024/4/24-9:55 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, nxt[N][2];

int next(int cur) {
    int n1 = nxt[cur][0], n2 = nxt[cur][1];
    if(nxt[n1][0] == n2 || nxt[n1][1] == n2) return n1;
    else return n2;
}

void solve() {
    if(n == 3) { // 特殊情况 只有3个人
        cout << "1 2 3";
        return;
    }
    int cur = 1;
    while(true) {
        cout << cur << " ";
        cur = next(cur);
        if(cur == 1) break;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nxt[i][0] >> nxt[i][1];
    solve();
};