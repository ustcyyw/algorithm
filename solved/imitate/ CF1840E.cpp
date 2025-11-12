/**
 * @Time : 2024/3/9-3:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 用cnt记录有多少个位置相等
  * 限制、交换时都查看原先该位置是否相等，以及操作后是否相等 来更新cnt
  * cnt + 限制的数量 = 字符串长度 说明相等
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
int T, n, m, t, q, cnt;
string s1, s2;

void solve() {
    cnt = 0;
    for(int i = 0; i < m; i++)
        cnt += s1[i] == s2[i];
    deque<pair<int, int>> dq; // (time, pos)
    for(int i = 0, type, k1, p1, k2, p2; i < q; i++) {
        if(!dq.empty() && i - dq.front().first == t) { // 解除限制的点
            int pos = dq.front().second;
            if(s1[pos] == s2[pos]) cnt++;
            dq.pop_front();
        }
        cin >> type;
        if(type == 1) {
            cin >> p1;
            dq.push_back({i, p1});
            if(s1[p1] == s2[p1]) cnt--;
        } else if(type == 2) {
            cin >> k1 >> p1 >> k2 >> p2;
            cnt -= (s1[p1] == s2[p1]) + (s1[p2] == s2[p2]);
            if(k1 == 1 && k2 == 1) swap(s1[p1], s1[p2]);
            if(k1 == 1 && k2 == 2) swap(s1[p1], s2[p2]);
            if(k1 == 2 && k2 == 1) swap(s2[p1], s1[p2]);
            if(k1 == 2 && k2 == 2) swap(s2[p1], s2[p2]);
            cnt += (s1[p1] == s2[p1]) + (s1[p2] == s2[p2]);
        } else {
            if(cnt + dq.size() == m) cout << "YES\n";
            else cout << "NO\n";
        }
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> s1 >> s2;
        cin >> t >> q;
        s1 = '.' + s1, s2 = '.' + s2;
        m = s1.size();
        solve();
    }
};