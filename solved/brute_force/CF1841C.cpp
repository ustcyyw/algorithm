/**
 * @Time : 2024/12/10-5:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1841C 1800 暴力枚举 前后缀分解
 */
/*
  * 枚举修改的位置i和要修改为的字母j
  * [i+1,n]上是原本的值 这部分值可以预处理
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, suf[N], maxV[N], point[5] = {1, 10, 100, 1000, 10000};
string s;

ll change(vector<int>& cnt, int j) {
    ll ans = 0;
    for(int k = 0; k < j; k++)
        ans = ans - 2 * cnt[k] * point[k];
    return ans;
}

void solve() {
    suf[n + 1] = 0, maxV[n + 1] = -1;
    for(int i = n, val = -1; i >= 1; i--) {
        int t = s[i] - 'A', add = point[t];
        suf[i] = t < val ? -add : add;
        suf[i] += suf[i + 1];
        val = max(val, t), maxV[i] = val;
    }
    vector<int> cnt(5, 0); // 记录截止i-1 右边还没有遇到更大字母的那些字母的数量
    ll ans = suf[1], pre = 0; // pre预先记录i-1的累加和
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 5; j++) {
            // 修改当前字母为j，并且考虑j右边的字母前面 前面位置的字母的贡献值要改变
            ll temp = pre + change(cnt, max(j, (int)maxV[i + 1])) + suf[i + 1];
            int add = j < maxV[i + 1] ? -point[j] : point[j];
            ans = max(ans, temp + add);
        }
        int t = s[i] - 'A';
        cnt[t]++, pre += point[t]; // 当前字母暂时没遇到更大的字母 贡献是正的 并且统计数量
        for(int j = 0; j < t; j++) { // 比当前字母小的字母，贡献值翻转 更新pre
            pre -= 2 * cnt[j] * point[j];
            cnt[j] = 0; // 已经遇到更大的字母 因此计数清0
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s;
        n = s.size();
        s = '.' + s;
        solve();
    }
};