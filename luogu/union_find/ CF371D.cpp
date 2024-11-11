/**
 * @Time : 2024/4/18-9:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 用a[i],water[i]分别表示容器的容积和现在装的水
 *
 * 并查集 每个分量的id就标识这个分量中最靠下的还有余量的容器的编号
 * 因此只要 p != find(p) 就说明这个容器满了 现在的水就是a[p]
 * 如果不满 其现在的水就是 water[p]
 *
 * add(p, x)向容器中假如x的水
 * 用n + 1表示地板这个特殊容器 其容积无限 如果p == n + 1
 * 如果 p == n + 1，往地板加水 结束这个过程
 * 如果 water[p] + x < a[p] 当前容器够放水 水添加后结束过程
 * 否则 当前容器水加满后 还有 x - (a[p] - water[p])向下溢出
 * 并且当前容器就和下一个容器p+1连接上了，将溢出的水向 find(p + 1)添加（下一个未满的容器）
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, k, a[N], water[N], id[N];

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return ;
    id[p] = q;
}

void add(int p, int x) {
    if(p == n + 1) return;
    if(water[p] + x < a[p]) {
        water[p] += x;
        return;
    }
    connect(p, p + 1);
    add(find(p + 1), x - (a[p] - water[p]));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = i;
    }
    id[n + 1] = n + 1; // 表示地板
    cin >> m;
    for(int i = 1, t, u, x; i <= m; i++) {
        cin >> t >> u;
        int p = find(u);
        if(t == 1) {
            cin >> x;
            add(p, x);
        } else {
            cout << (u != p ? a[u] : water[u]) << "\n";
        }
    }
};