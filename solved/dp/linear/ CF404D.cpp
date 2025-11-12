/**
 * @Time : 2023/12/7-10:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
string s;
vector<vector<long long>> cache;
/*
 * 当前字符用c表示，i表示当前考虑的位置
 * bomb: 表示炸弹情况 一共3种状态
 * 0: 右边不是炸弹 也不需要炸弹
 *    0.a: c 为 * 或者 2。都不满足 不需要计算，直接设置 cnt = 0
 *    0.b: c 为 0 或者 1。那么考虑第 i-1 位置的时候 分别需要0个或1个炸弹
 *    0.c: c 为 ? 那么可以设置为 0或者1 两种方案相加
 * 1：右边不是炸弹 但需要1个炸弹
 *    1.a: c 为0、1、2 都无法为右边提供1个炸弹 应该都不用计算，直接设置 cnt = 0
 *    1.b: c 为 * 或者 ? 都只能将当前位置当炸弹为右边提供1个炸弹
 * 2：右边是一个炸弹的情况
 *    2.a: c为0 无法满足
 *    2.b: c为1或者2，右边提供了一个炸弹，那么当前位置还需要 c - 1 个炸弹
 *    2.c: c为*，允许两个炸弹连着放置
 *    2.d: c为?，可以设置为1、2、* 对应了上面说过的情况，进行加和
 */
long long dfs(int i, int bomb) {
    char c = s[i];
    if(i == 0) {
        if(c == '0') return bomb == 0;
        if(c == '1') return bomb == 2;
        if(c == '*') return bomb == 1 || bomb == 2;
        return bomb == 2 ? 2 : 1;
    }
    if(cache[i][bomb] != -1) return cache[i][bomb];
    long long cnt = 0;
    if(bomb == 0) { // 右边不是炸弹 也不需要炸弹
        if(c == '0' || c == '1') cnt = dfs(i - 1, c - '0');
        if(c == '?') cnt = dfs(i - 1, 1) + dfs(i - 1, 0);
    } else if (bomb == 1) { // 右边不是炸弹 但需要1个炸弹
        if(c == '*' || c == '?') cnt = dfs(i - 1, 2);
    } else { // 右边是一个炸弹的情况
        if(c == '1' || c == '2') cnt = dfs(i - 1, c - '0' - 1);
        if(c == '*') cnt = dfs(i - 1, 2);
        if(c == '?') cnt = dfs(i - 1, 0) + dfs(i - 1, 1) + dfs(i - 1, 2);
    }
    cnt %= mod;
    cache[i][bomb] = cnt;
    return cnt;
}

long long solve() {
    int n = s.size();
    char last = s[n - 1];
    if(last == '2' || s[0] == '2') return 0; // 头尾巴是2 绝对不可能
    if(n == 1) {
        if(last == '1') return 0;
        if(last == '0' || last == '*') return 1;
        return 2; // 是问号的情况
    }
    cache.assign(n, vector(3, -1ll));
    if(last == '1' || last == '0') return dfs(n - 2, last - '0');
    if(last == '*') return dfs(n - 2, 2);
    // 最后一个字符是问号的情况
    return (dfs(n - 2, 2) + dfs(n - 2, 1) + dfs(n - 2, 0)) % mod;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    cout << solve() << endl;
}