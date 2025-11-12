/**
 * @Time : 2024/2/2-9:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 处理矛盾关系 并查集
 */
/*
 * 处理矛盾关系 可以使用并查集
 * 矛盾关系可以具象化为 朋友-敌人的关系
 * 即：是朋友的一定不是敌人；反之也成立。 但是敌人的敌人 就是朋友
 *
 * 用i表示i的朋友的编号；用i+n表示i的敌人的编号
 *
 * 那么当i和j是敌人的时候 j就与i+n是同类（等价类）因此将j和i+n进行合并
 * 且i就和j的敌人是朋友 i与j+n是同类 因此将j和i+n进行合并
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
int T, n, id[2 * N];

int find(int p) {
    if(id[p] == p) return p;
    return id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    id[p] = q;
}

long long get_key(int a, int b) {
    return min(a, b) * N + max(a, b);
}

bool solve() {
    vector<vector<int>> pair(n + 1);
    unordered_map<long long, int> map;
    bool flag = false;
    for(int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        if(flag) continue;
        pair[a].push_back(b), pair[b].push_back(a);
        map[get_key(a, b)] = i;
        if(a == b || pair[a].size() > 2 || pair[b].size() > 2) flag = true;
    }
    if(flag) return true;
    for(int k = 1; k <= n; k++) {
        long long k1 = get_key(k, pair[k][0]), k2 = get_key(k, pair[k][1]);
        int i = map[k1], j = map[k2];
        if(i == j) continue; // 两个数字都想同的数对 直接放两个集合即可 不需要记录矛盾关系
        connect(i + n, j), connect(i, j + n);
        // 自己和自己的敌人归到一个类 发生矛盾了
        if(find(i) == find(i + n) || find(j) == find(j + n))
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= 2 * n; i++)
            id[i] = i;
        cout << (solve() ? "NO" : "YES") << "\n";
    }
};