/**
 * @Time : 2024/6/18-2:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1283D bfs 贪心
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, m;
set<int> marked;
queue<int> q;

int add(vector<int>& pos, ll& ans, ll step, int x) {
    if(marked.count(x)) return 0;
    ans += step;
    marked.insert(x), q.push(x), pos.push_back(x);
    return 1;
}

void solve() {
    ll ans = 0, step = 1, cnt = 0;
    vector<int> pos;
    while(cnt != m) {
        int sz = q.size();
        while(sz-- > 0) {
            int x = q.front(), x1 = x + 1, x2 = x - 1;
            cnt += add(pos, ans, step, x1);
            if(cnt == m) break;
            cnt += add(pos, ans, step, x2);
            if(cnt == m) break;
            q.pop();
        }
        step++;
    }
    cout << ans << "\n";
    for(int x : pos)
        cout << x << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, num; i <= n; i++){
        cin >> num;
        marked.insert(num), q.push(num);
    }
    solve();
};