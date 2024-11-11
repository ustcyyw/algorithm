/**
 * @Time : 2024/7/13-10:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1579D
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n;
vector<vector<int>> ans;
map<int, deque<int>> mp;

void make(int c1, int c2, deque<int>& p1, deque<int>& p2) {
    int id1 = p1.front(), id2 = p2.back();
    p1.pop_front(), p2.pop_back();
    if(c1 - 1 > 0) mp[c1 - 1].push_back(id1);
    if(c2 - 1 > 0) mp[c2 - 1].push_back(id2);
    ans.push_back({id1, id2});
    if(p1.empty()) mp.erase(c1);
    if(c1 != c2 && p2.empty()) mp.erase(c2);
}

void solve() {
    while(!mp.empty()) {
        auto& p1 = *mp.begin();
        auto& p2 = *mp.rbegin();
        int c1 = p1.first, c2 = p2.first;
        if(c1 == c2 && p1.second.size() == 1) break;
        make(c1, c2, p1.second, p2.second);
    }
    cout << ans.size() << "\n";
    for(auto& p : ans)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        ans = {}, mp = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(num) mp[num].push_back(i);
        }
        solve();
    }
};