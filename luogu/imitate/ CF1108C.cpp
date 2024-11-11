/**
 * @Time : 2024/4/29-4:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1108C
 */
/*
 * 题目的要求 等价于下标 mod 3相等的字符 都得相等
 * 枚举前3个字符 其它地方的字符按前3个字符更改
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n;
char base[3] = {'R', 'G', 'B'};
unordered_map<char, int> cnt[3];
string s;

void solve() {
    int m = n / 3, mod = n % 3;
    int m1 = mod > 0 ? m + 1 : m, m2 = mod > 1 ? m + 1 : m, m3 = m;
    for(int i = 0; i < n; i++) {
        cnt[i % 3][s[i]]++;
    }
    vector<char> color;
    int cnt1, cnt2, cnt3, res = INT_MAX;
    for(char c1 : base) {
        cnt1 = m1 - cnt[0][c1];
        for(char c2 : base) {
            if(c2 == c1) continue;
            cnt2 = m2 - cnt[1][c2];
            for(char c3 : base) {
                if(c3 == c1 || c3 == c2) continue;
                cnt3 = m3 - cnt[2][c3];
                if(res > cnt1 + cnt2 + cnt3) {
                    res = cnt1 + cnt2 + cnt3;
                    color = {c1, c2, c3};
                }
            }
        }
    }
    cout << res << "\n";
    for(int i = 0; i < n; i++)
        s[i] = color[i % 3];
    cout << s;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    solve();
};