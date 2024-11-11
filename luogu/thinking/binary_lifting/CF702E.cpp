/**
 * @Time : 2024/3/30-3:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * k很大 并且求的是一段连续路径（区间）上的和与最值
  * 典型的倍增题目
  * f[x][i] : 表示与x结点距离为 2 ^ i 结点
  * sum[x][i]: 表示从x结点出发的 2 ^ i 长度的路径和
  * mv[x][i]: 表示从x结点出发的 2 ^ i 长度的路径上的最小权值
  *
  * f[x][i + 1] = f[f[x][i]][i], v = f[x][i]: x的2^i距离的结点
  * w = f[v][i]：距离v的2^i距离的结点， 从x到v有2^i，从v到w有2^i距离
  * 因此x到w的距离为2^(i + 1)
  * sum[x][i + 1] = sum[v][i] + sum[x][i]
  * mv[x][i + 1] = min(mv[v][i], mv[x][i])
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
ll T, n, k, f[N][34], mv[N][34], sum[N][34];

void find(int x) {
    ll s = 0, val = LONG_LONG_MAX;
    for(int i = 33; i >= 0; i--) {
        if(((1ll << i) & k) == 0) continue;
        s += sum[x][i], val = min(val, mv[x][i]);
        x = f[x][i];
    }
    cout << s << " " << val << "\n";
}

void solve() {
    for(int i = 1; i < 34; i++) {
        for(int x = 0; x < n; x++) {
            int v = f[x][i - 1];
            f[x][i] = f[v][i - 1];
            sum[x][i] = sum[v][i - 1] + sum[x][i - 1];
            mv[x][i] = min(mv[v][i - 1], mv[x][i - 1]);
        }
    }
    for(int x = 0; x < n; x++)
        find(x);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 0, v; i < n; i++) {
        cin >> v;
        f[i][0] = v;
    }
    for(int i = 0, weight; i < n; i++) {
        cin >> weight;
        mv[i][0] = weight, sum[i][0] = weight;
    }
    solve();
};