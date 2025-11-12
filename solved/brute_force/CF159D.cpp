/**
 * @Time : 2025/3/6-10:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF159D 1500 暴力枚举
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2000 + 5, P = 13331;
ll n, pal[N][N], sum[N];
string s;

void check(int lo, int hi) {
    while(lo >= 0 && hi < n && s[lo] == s[hi]) {
        pal[lo][hi] = 1;
        lo--, hi++;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    n = s.size();
    for(int i = 0; i < n; i++)
        check(i, i), check(i, i + 1);
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i; j >= 0; j--) {
            if(pal[j][i]) {
                if(j > 0) ans += sum[j - 1];
                sum[i]++;
            }
        }
        if(i > 0) sum[i] += sum[i - 1];
    }
    cout << ans << "\n";
}