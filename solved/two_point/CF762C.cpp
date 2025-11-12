/**
 * @Time : 2025/2/20-9:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF762C 2100 前后缀分解 双指针
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5;
int n, m, len = 0, l, r; // len是删除后t的长度， t[l,r]是要被删除的子串
string s, t;

// pre[i]: 表示使用了s[0,i]可以匹配t[0, pre[i]]
vector<int> get_pre() {
    vector<int> pre(n, -1);
    for(int i = 0, j = 0; i < n; i++) {
        if(i > 0) pre[i] = pre[i - 1];
        if(s[i] == t[j]) {
            pre[i] = j;
            j++;
        }
    }
    return pre;
}
// suf[i]: 表示使用了s[i, n-1]可以匹配t[suf[i], m-1]
vector<int> get_suf() {
    vector<int> suf(n, m);
    for(int i = n - 1, j = m - 1; i >= 0; i--) {
        if(i != n - 1) suf[i] = suf[i + 1];
        if(s[i] == t[j]) {
            suf[i] = j;
            j--;
        }
    }
    return suf;
}

string solve() {
    vector<int> pre = get_pre(), suf = get_suf();
    if(pre[n - 1] == m - 1) return t; // 可以不用删任何东西的情况
    // 删t的后缀的情况
    len = pre[n - 1] + 1, l = pre[n - 1] + 1, r = m - 1;
    // 删除t的前缀的情况
    if(len < m - suf[0]) len = m - suf[0], l = 0, r = suf[0] - 1;
    // 删除t的中间一个子串
    for(int i = 0; i < n - 1; i++) {
        if(pre[i] == -1) continue;
        int lo = pre[i] + 1, hi = suf[i + 1] - 1;
        int temp = m - (hi - lo + 1);
        if(temp > len) len = temp, l = lo, r = hi;
    }
    if(len == 0) return "-";
    string left = t.substr(0, l), right = t.substr(r + 1);
    return left + right;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> s >> t;
    n = s.size(), m = t.size();
    cout << solve() << "\n";
};