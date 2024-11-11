/**
 * @Time : 2024/2/2-2:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 处理矛盾关系 可以使用并查集
 * 从大的冲突开始处理 让他们分在不同的集合
 * 当前冲突决定了 两个人分属的集合
 * 如果为解决当前冲突 导致了两个人与其敌人分配到一组了
 * 那就只能让当前冲突发生 这就是能调配的最小冲突了
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e4 + 5, M = 1e5 + 5;
int n, m, id[2 * N];
vector<vector<int>> e;

int find(int p) {
    if(id[p] == p) return p;
    return id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    id[p] = q;
}

int solve() {
    for(int i = m - 1; i >= 0; i--) {
        int a = e[i][0], b = e[i][1], w = e[i][2];
        connect(a, b + n), connect(a + n, b); // a放在b的敌人集合。b放在a的敌人集合
        if(find(a) == find(a + n) || find(b) == find(b + n))
            return w;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    e = {};
    for(int i = 1; i <= 2 * n; i++)
        id[i] = i;
    for(int i = 1, a, b, w; i <= m; i++) {
        cin >> a >> b >> w;
        e.push_back({a, b, w});
    }
    sort(e.begin(), e.end(), [](auto& a, auto& b) -> bool {return a[2] < b[2];});
    cout << solve() << endl;
};