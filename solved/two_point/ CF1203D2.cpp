/**
 * @Time : 2024/5/17-5:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1203D2 双指针 + 前后缀分解
 */
 /*
  * easy版本只有数据范围不同
  * 删除s的一个子串 让t仍然是s的子序列
  * 前后缀分解
  * 预处理 pre[i]: 从左到右截止s[i]能找到t的最长前缀长度
  *       suf[i]: 从右到左截止s[i]能找到t的最长后缀长度
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, n, m, pre[N], suf[N];
string s, t;

void solve() {
    n = s.size(), m = t.size();
    int ans = 0;
    for(int i = 0, j = 0; i < n; i++) {
        if(j < m && s[i] == t[j]) j++;
        pre[i] = j;
        if(pre[i] == m) ans = max(ans, n - i - 1);
    }
    for(int i = n - 1, j = m - 1; i > 0; i--) {
        if(j < m && s[i] == t[j]) j--;
        suf[i] = m - 1 - j;
        if(suf[i] == m) ans = max(ans, i);
    }
    for(int i = 0, j = 1; i < n; i++) {
        while(j < n && pre[i] + suf[j] >= m) j++;
        ans = max(ans, j - 2 - (i + 1) + 1);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s >> t;
    solve();
};