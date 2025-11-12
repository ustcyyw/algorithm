/**
 * @Time : 2025/1/4-5:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2045C 1400 贪心
 */
/*
  * 选择的前缀、后缀 只要有1个字母交叉 就可以拆分成两组前缀、后缀
  * 找到相同字母的s中最短前缀和t中最短后缀 拼接在一起就是一个备选答案
  * 并且前缀和后缀长度 > 1 不然在拆分两组的时候 其中一组会出现空串
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k;
string s, t;

string solve() {
    vector<int> pre(26, -1), suf(26, -1);
    for(int i = 1; i < s.size(); i++) {
        int c = s[i] - 'a';
        if(pre[c] == -1) pre[c] = i;
    }
    for(int i = t.size() - 2; i >= 0; i--) {
        int c = t[i] - 'a';
        if(suf[c] == -1) suf[c] = i;
    }
    string ans;
    for(int i = 0; i < 26; i++) {
        if(pre[i] != -1 && suf[i] != -1) {
            string temp = s.substr(0, pre[i] + 1) + t.substr(suf[i] + 1);
            if(ans.empty() || temp.size() < ans.size())
                ans = temp;
        }
    }
    return ans.empty() ? "-1" : ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> s >> t;
        cout << solve();
    }
};