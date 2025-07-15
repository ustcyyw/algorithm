/**
 * @Time : 2025/7/1-16:38
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2117E 1600 暴力枚举 分情况讨论
 */
 /*
  * 可以在进行最多一次删除操作，枚举要删除的那一列
  * 赋值是从后到前，并且都是固定位置可以相互覆盖
  * 如果可以通过赋值操作 使得某一列a[i] = b[i]，这之前就都可以变为相同值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
int T, n, a[N], b[N], up[N], down[N];

int solve() {
    if(a[n] == b[n]) return n;
    up[a[1]]--, down[b[1]]--;
    int ans = 0;
    for(int i = 1; i < n; i++) {
        if(a[i] == b[i]) ans = i;
        if(i % 2 == 1) {
            if(up[b[i]] > 0 || down[a[i]] > 0) ans = i;
            up[b[i + 1]]--, down[a[i + 1]]--;
            if(up[a[i]] > 0 || down[b[i]] > 0) ans = i;
        }
        else {
            if(up[a[i]] > 0 || down[b[i]] > 0) ans = i;
            up[a[i + 1]]--, down[b[i + 1]]--;
            if(up[b[i]] > 0 || down[a[i]] > 0) ans = i;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(down, down + n + 1, 0), fill(up, up + n + 1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            if(i % 2 == 1) up[a[i]]++;
            else down[a[i]]++;
        }
        for(int i = 1; i <= n; i++) {
            cin >> b[i];
            if(i % 2 == 0) up[b[i]]++;
            else down[b[i]]++;
        }
        cout << solve() << "\n";
    }
}