/**
 * @Time : 2024/3/21-5:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 本题只能使用3个字母 abc
  * 为了不出现任何一个子串是回文串 就要求该区间上
  * 任意相邻的两个位置字母不同，间隔一个位置的字母不同
  * 于是在前两个字母确定的情况下，第三个字母唯一确定
  * 稍微举例发现字母的顺序是循环的 比如开头两字母是ab，那么第三个字母是c 第四个字母就只能是a
  * 这个序列就是 abcabcabc
  * 开头字母共6种组合 序列共6种 并且可以保证在s的开头设定6种情况
  * 能让任意一个子区间[l,r]的开头两字母s[l],s[l+1]也有6种情况
  * 因此将6种开头情况下，s需要修改字符数的前缀和预处理即可
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int T, n, m, sum[6][N];
string s, pat[6] = {"abc", "acb", "bac", "bca", "cab", "cba"};

void get_sum(int k) {
    for(int i = 1, j = 0; i <= n; i++, j = (j + 1) % 3)
        sum[k][i] = sum[k][i - 1] + (s[i] != pat[k][j]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    cin >> s;
    s = '.' + s;
    for(int i = 0; i < 6; i++)
        get_sum(i);
    for(int i = 0, l, r; i < m; i++) {
        cin >> l >> r;
        int ans = INT_MAX;
        for(auto& t : sum)
            ans = min(ans, t[r] - t[l - 1]);
        cout << ans << "\n";
    }
};