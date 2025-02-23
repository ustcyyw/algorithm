/**
 * @Time : 2025/2/22-8:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF797C 1700 贪心 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5;
int n, suf[N][26];
string s;

int find(int idx) {
    for(int j = 0; j < 26; j++) {
        if(suf[idx][j]) return j;
    }
    return -1;
}

void solve() {
    string ans;
    stack<char> stack;
    for(int i = 0; i < n;) {
        int j = i, c1 = find(i);
        while(j < n && suf[j][c1] > 0) {
            if(s[j] - 'a' == c1) ans.push_back(s[j]);
            else stack.push(s[j]);
            j++;
        }
        int c2 = find(j);
        while(!stack.empty() && stack.top() - 'a' <= c2)
            ans.push_back(stack.top()), stack.pop();
        i = j;
    }
    while(!stack.empty())
        ans.push_back(stack.top()), stack.pop();
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> s;
    n = s.size();
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < 26; j++)
            suf[i][j] = suf[i + 1][j];
        suf[i][s[i] - 'a']++;
    }
    solve();
};