/**
 * @Time : 2024/5/15-10:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m, mp[50];
set<int> st[6];

int init = []() -> int {
    mp[4] = 0, mp[8] = 1, mp[15] = 2, mp[16] = 3, mp[23] = 4, mp[42] = 5;
    return 0;
}();

void solve() {
    int ans = 0;
    while(!st[0].empty()) {
        vector<int> remove;
        int idx = *st[0].begin();
        remove.push_back(idx);
        for(int i = 1; i < 6; i++) {
            auto it = st[i].lower_bound(idx);
            if(it == st[i].end()) break;
            idx = *it;
            remove.push_back(idx);
        }
        if(remove.size() != 6) break;
        for(int i = 0; i < 6; i++)
            st[i].erase(st[i].find(remove[i]));
        ans += 6;
    }
    cout << n - ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        int idx = mp[num];
        st[idx].insert(i);
    }
    solve();
};