/**
 * @Time : 2024/2/2-10:57 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 处理矛盾关系 可以使用并查集
 * a和b是朋友 他们应该在一个集合 合并
 * a和b是敌人 那么b应该和a的敌人是朋友，a和b的敌人是朋友。
 * 需要记录每个人出现的第一个敌人 这个人所在的集合就是它的敌人集合。敌人集合中的所有人就是朋友
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1005;
int n, m, id[N];

int find(int p) {
    if(id[p] == p) return p;
    return id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    id[p] = q;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    vector<int> e(n + 1, -1);
    for(int i = 1; i <= n; i++)
        id[i] = i;
    char c;
    for(int i = 1, a, b; i <= m; i++) {
        cin >> c;
        cin >> a >> b;
        if(c == 'F') connect(a, b);
        else {
            if(e[a] != -1) connect(e[a], b); // a已经存在敌人了 那么b和那个a的敌人是朋友
            if(e[b] != -1) connect(e[b], a);
            e[a] = b, e[b] = a;
        }
    }
    unordered_set<int> set;
    for(int i = 1; i <= n; i++)
        set.insert(find(i));
    cout << set.size() << endl;
};