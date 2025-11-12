/**
 * @Time : 2024/5/21-3:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 四个方向剩余的位置 都是单调向内收缩
  * 那么外围的点不断被人拿到 因此可以分别对横坐标 纵坐标排序
  * 根据切割方式不断单调移除点 移除的时候注意另外一个坐标在当前限制范围内
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, a, b, n, m;
vector<vector<int>> row, col;
deque<vector<int>> rq, cq;

void input_queue(deque<vector<int>>& q, vector<vector<int>>& arr) {
    for(auto& point : arr)
        q.push_back(point);
}
// flag = 1 表示从队头出
void remove(deque<vector<int>>& q, int& cnt, int flag, int t, int b1, int b2) {
    while(!q.empty()) {
        int p1, p2;
        if(flag) {
            p1 = q.front()[0], p2 = q.front()[1];
            if(p1 > t) break;
            q.pop_front();
        } else {
            p1 = q.back()[0], p2 = q.back()[1];
            if(p1 < t) break;
            q.pop_back();
        }
        if(p2 > b1 && p2 < b2) cnt++;
    }
}

void solve() {
    char type;
    bool flag = true;
    int c1 = 0, c2 = 0, left = 0, up = 0, down = a + 1, right = b + 1;
    for(int i = 1, k; i <= m; i++, flag = !flag) {
        cin >> type;
        cin >> k;
        if(type == 'U') {
            up += k;
            remove(rq, flag ? c1 : c2, true, up, left, right);
        } else if(type == 'D') {
            down -= k;
            remove(rq, flag ? c1 : c2, false, down, left, right);
        } else if(type == 'L') {
            left += k;
            remove(cq, flag ? c1 : c2, true, left, up, down);
        } else {
            right -= k;
            remove(cq, flag ? c1 : c2, false, right, up, down);
        }
    }
    cout << c1 << " " << c2 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> a >> b >> n >> m;
        row.clear(), col.clear(), rq.clear(), cq.clear();
        for(int i = 1, x, y; i <= n; i++) {
            cin >> x >> y;
            row.push_back({x, y}), col.push_back({y, x});
        }
        sort(row.begin(), row.end());
        input_queue(rq, row);
        sort(col.begin(), col.end());
        input_queue(cq, col);
        solve();
    }
};