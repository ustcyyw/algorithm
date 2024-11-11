/**
 * @Time : 2024/7/9-8:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1506G 贪心
 */
 /*
  * 当前能留下的字母中 选最大的一个留下
  * 能留下的字母c要满足 每个还没被选择的字母 至少都在c的右边出现一次
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, m, cnt;
deque<int> dqs[26];
string s;

bool check(int i) {
    for(int j = 25; j >= 0; j--) {
        if(j == i || dqs[j].empty()) continue;
        if(dqs[j].back() < dqs[i].front())
            return false;
    }
    return true;
}

int pick() {
    for(int i = 25; i >= 0; i--) {
        if(dqs[i].size() == 0) continue;
        if(check(i)) return i;
    }
    return -1;
}

void remove(int i) {
    for(int j = 25; j >= 0; j--) {
        if(j == i || dqs[j].empty()) continue;
        while (dqs[j].front() < dqs[i].front())
            dqs[j].pop_front();
    }
    dqs[i].clear();
}

void solve() {
    for(int i = 0; i < 26; i++)
        if(dqs[i].size() > 0) cnt++;
    string ans;
    while(cnt-- > 0) {
        int c = pick();
        ans.push_back((char)(c + 'a'));
        remove(c);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s;
        cnt = 0;
        for(int i = 0; i < 26; i++)
            dqs[i] = {};
        for(int i = 0; i < s.size(); i++)
            dqs[s[i] - 'a'].push_back(i);
        solve();
    }
};