/**
 * @Time : 2024/8/5-5:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1729F 暴力枚举 字符串hash
 */
/*
 * 暴力枚举
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5, mod = 9;
typedef long long ll;
int T, n, w, m, power10[N], h[N], l1[10], l2[10];
string s;

int get_mod(int l, int r) {
    return (((h[r] - h[l - 1] * power10[r - l + 1]) % mod) + mod) % mod;
}


void init() {
    // 参数s已经在前缀添加一个哨兵字符 有效下标从1开始
    power10[0] = 1;
    for(int i = 1; i <= n; i++) {
        h[i] = (h[i - 1] * 10 + s[i] - '0') % mod;
        power10[i] = power10[i - 1] * 10 % mod;
    }
    for(int i = 1; i + w - 1 <= n; i++) {
        int code = get_mod(i, i + w - 1);
        if(l1[code] == 0) l1[code] = i;
        else if(l2[code] == 0) l2[code] = i;
    }
}

void query(int l, int r, int k) {
    int c = get_mod(l, r);
    int al = INT_MAX, bl = INT_MAX;
    for(int a = 0; a < 9; a++) {
        if(l1[a] == 0) continue;
        for(int b = 0; b < 9; b++) {
            if((a * c % mod + b) % mod != k) continue;
            if((a == b && l2[a] == 0) || (a != b && l1[b] == 0)) continue;
            if(a == b) {
                if(al > l1[a] || (al == l1[a] && bl > l2[a]))
                    al = l1[a], bl = l2[a];
            } else {
                if(al > l1[a] || (al == l1[a] && bl > l1[b]))
                    al = l1[a], bl = l1[b];
            }
        }
    }
    if(al == INT_MAX) cout << -1 << " " << -1 << "\n";
    else cout << al << " " << bl << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s >> w >> m;
        n = s.size();
        s = '.' + s;
        memset(l1, 0, sizeof(l1)), memset(l2, 0, sizeof(l2));
        init();
        for(int i = 1, l, r, k; i <= m; i++) {
            cin >> l >> r >> k;
            query(l, r, k);
        }
    }
};