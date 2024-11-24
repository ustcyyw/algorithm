/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;
string s1, s2;

vector<int> statistic(string& s) {
    vector<int> cnt(26, 0);
    for(char c : s)
        cnt[c - 'a']++;
    return cnt;
}
// 计算逆序对
int count_reverse(string& s) {
    int ans = 0;
    for(int i = 1; i < s.size(); i++) {
        for(int j = 0; j < i; j++)
            if(s[i] < s[j]) ans++;
    }
    return ans;
}

bool solve() {
    vector<int> cnt1 = statistic(s1), cnt2 = statistic(s2);
    if(cnt1 != cnt2) return false;
    bool same = false; // 标识一个字符串中是否出现了相同的字母
    for(int num : cnt1) {
        same |= num > 1;
    }
    if(same) return true;
    // 字符串长度超过26， 一定会有相同字母出现， 可以断定现在字符串长度最多26
    int c1 = count_reverse(s1), c2 = count_reverse(s2);
    return abs(c1 - c2) % 2 == 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> s1 >> s2;
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};