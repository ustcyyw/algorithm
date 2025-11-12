/**
 * @Time : 2024/6/7-3:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1714F 构造 + 数学
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, MV = 1e9;
typedef long long ll;
int T, n, node, d12, d23, d13;
vector<vector<int>> edge;

// 结点start为起点 end为终点 二者之间还需要插入cnt个结点
void link(int start, int end, int cnt) {
    int pre = start;
    for(; cnt; cnt--) {
        edge.push_back({pre, ++node});
        pre = node;
    }
    edge.push_back({pre, end});
}

bool solve() {
    if(d12 + d23 == d13) { // 2在1和3之间
        link(1, 2, d12 - 1), link(2, 3, d23 - 1);
    } else if(d23 == d13 + d12) { // 1在2和3之间
        link(1, 2, d12 - 1), link(1, 3, d13 - 1);
    } else if(d13 + d23 == d12) { // 3在1和2之间
        link(1, 3, d13 - 1), link(3, 2, d23 - 1);
    } else { // 1和2先连起来 然后在1和2之间找一个中介点 从这点引入一条边链接到3 画图计算距离
        if(d12 == 1 || d13 == 1 || d23 == 1) return false;
        int t = d13 + d23 - d12, h = t / 2;
        if(t % 2 != 0 || t <= 0) return false;
        link(1, 2, d12 - 1);
        int dis = d13 - h;
        if(dis <= 0 || dis + 3 > n || dis > d12 - 1) return false;
        link(dis + 3, 3, h - 1);
    }
    if(node > n) return false;
    while(node < n)
        edge.push_back({++node, 1});
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> d12 >> d23 >> d13;
        edge.clear();
        node = 3;
        int flag = solve();
        cout << (flag ? "YES" : "NO") << "\n";
        if(flag) {
            for(auto& p : edge) {
                cout << p[0] << " " << p[1] << "\n";
            }
        }
    }
};