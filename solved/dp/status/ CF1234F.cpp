/**
 * @Time : 2024/6/15-3:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1234F 状态压缩dp
 */
/*
 * 字符集只有20 考虑状态压缩
 * 翻转子串 相当于是当前子串str[i,j]和翻转过来的子串sub拼接在一起
 * 只要需要翻转过来的字母在当前子串的右侧(j的右侧) 总能把他们翻转过来刚好贴在一起
 * 记str[i,j]对应的状态为s，那么sub对应的状态是(u ^ s)的子集合
 * 于是需要找到在str[j+1, n-1]上的子串sub是(u ^ s)的子集 并且长度最大
 * 因此可以预处理
 * aux[s][k]: 状态为s的子集中1的个数为j对应的子串的最大开头下标
 * 去找aux[u ^ s]中最大的k满足 aux[u^s][k] > j
 *
 * 预处理的方案 动态规划
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1048576 + 5, mod = 998244353;
typedef long long ll;
int T, n, u = 0, aux[N][21] = {0}, marked[N];
string str;

void suf_status() {
    for(int i = 0; i < n; i++) {
        int s = 0;
        for(int j = i; j < n; j++) {
            int t = 1 << (str[j] - 'a');
            if(s & t) break;
            s |= t;
            aux[s][j - i + 1] = i;
        }
    }
}

void dfs(int s) {
    if(marked[s]) return;
    marked[s] = 1;
    for(int i = 0; i < 20; i++) {
        int t = 1 << i;
        if((s & t) == 0) continue;
        int ns = s ^ t;
        dfs(ns);
        for(int j = 1; j <= 20; j++)
            aux[s][j] = max(aux[s][j], aux[ns][j]);
    }
}

int cal(int lo, int s) {
    for(int j = 20; j >= 1; j--) {
        if(aux[s][j] > lo) return j;
    }
    return 0;
}

void solve() {
    for(char c : str)
        u |= 1 << (c - 'a');
    suf_status();
    dfs(u);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int s = 0;
        for(int j = i; j < n; j++) {
            int t = 1 << (str[j] - 'a');
            if(s & t) break;
            s |= t;
            int us = u ^ s, len = cal(j, us);
            ans = max(ans, j - i + 1 + len);
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> str;
    n = str.size();
    solve();
};