/**
 * @Time : 2025/3/6-11:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF835D 1900 动态规划
 */
 /*
  * 一个字符串是最高是k阶 那么可以认为其是1阶、2阶...k阶
  * 题目要求的左子串、右子串分别是回文串 并且要相等
  * 这个条件可以推出来 当前字符串也是回文串 因此预处理回文串信息即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5000 + 5, P = 13331;
int n, pal[N][N], diff[N], cache[N][N];
string s;

void check(int lo, int hi) {
    while(lo >= 0 && hi < n && s[lo] == s[hi]) {
        pal[lo][hi] = 1;
        lo--, hi++;
    }
}

int dfs(int lo, int hi) {
    if(lo == hi) return 1;
    if(cache[lo][hi] != -1) return cache[lo][hi];
    if(!pal[lo][hi]) return 0;
    int half = (lo + hi) >> 1, len = hi - lo + 1;
    int m1, m2, ans;
    if(len % 2 == 1) m1 = half - 1, m2 = half + 1;
    else m1 = half, m2 = half + 1;
    if(pal[lo][m1] && pal[m2][hi]) ans = dfs(lo, m1) + 1;
    else ans = 1;
    return cache[lo][hi] = ans;
}

void solve() {
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            int k = dfs(i, j);
            if(k > 0) diff[1]++, diff[k + 1]--;
        }
    }
    for(int sum = 0, i = 1; i <= n; i++) {
        sum += diff[i];
        cout << sum << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    n = s.size();
    memset(cache, -1, sizeof(cache));
    for(int i = 0; i < n; i++)
        check(i, i), check(i, i + 1);
    solve();
}