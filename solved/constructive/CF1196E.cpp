/**
 * @Time : 2024/5/16-10:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1196E 贪心 + 构造
 */
 /*
  * 先想办法尽量多拿多的那种颜色 等两种颜色一样多 就可以朝一个方向一对一对的取
  * 怎么尽量多拿 就是以少的那种颜色为中心 将周围没拿过的另外一种颜色都拿上
  * 并且朝两个方向曲折延伸 不要朝一个方向延伸
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, b, w, n, m, dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};
vector<vector<int>> ans;
unordered_set<ll> picked;

bool add(int x, int y) {
    ll key = x * D + y;
    if(picked.count(key)) return true;
    if((x + y) % 2 == 1) {
        if(b > 0) b--;
        else return false;
    }
    else {
        if(w > 0) w--;
        else return false;
    }
    picked.insert(key), ans.push_back({x, y});
    return true;
}

void dfs(int x, int y, int dire) {
    if(b == 0 || w == 0) return;
    if(b == w) {
        ans.push_back({x, y}), ans.push_back({x + 1, y});
        b--, w--;
        dfs(x + 2, y, dire);
        return;
    }
    if(!add(x, y)) return;
    for(int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if(!add(nx, ny)) return;
        if(b == w) break;
    }
    if(dire) dfs(x + 2, y, !dire);
    else dfs(x, y + 2, !dire);
}

void solve() {
    if(b > w) dfs(2, 2, 0); // 黑色更多
    else dfs(2, 3, 0);
    if(b == 0 && w == 0) {
        cout << "YES\n";
        for(auto& p : ans)
            cout << p[0] << " " << p[1] << "\n";
    } else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> b >> w;
        ans.clear(), picked.clear();
        solve();
    }
};