/**
 * @Time : 2024/5/9-8:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1968G1 二分 + kmp
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, l, r;
string s;

vector<int> kmp(string &text, string pattern) {
    int m = pattern.length();
    vector<int> pi(m), res;
    for (int i = 1, c = 0; i < m; i++) {
        char v = pattern[i];
        while (c && pattern[c] != v)
            c = pi[c - 1];
        if (pattern[c] == v) c++;
        pi[i] = c;
    }
    for (int i = 0, c = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v)
            c = pi[c - 1];
        if (pattern[c] == v) c++;
        if (c == m) {
            res.push_back(i - m + 1);
            c = pi[c - 1];
        }
    }
    return res;
}

bool check(int len) {
    vector<int> arr = kmp(s, s.substr(0, len));
    int cnt = 1;
    for(int i = 0, m = arr.size(), j, b; i < m; ) {
        j = i, b = arr[i] + len;
        while(j < m && arr[j] < b) j++;
        if(j != m) cnt++;
        if(cnt >= r) return true;
        i = j;
    }
    return false;
}

void solve() {
    int lo = 0, hi = n / r;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> l >> r;
        cin >> s;
        solve();
    }
};