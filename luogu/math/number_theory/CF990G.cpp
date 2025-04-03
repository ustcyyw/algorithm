/**
 * @Time : 2025/4/3-12:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF990G 2400 数学 数论 dp 并查集
 */
/*
  * 定义f[i]: 路径x,y的gcd值是i的倍数的路径数目
  * 假设 最终答案中存在gcd值 i, 2i, 4i, 5i
  * 那么f[4i]就是gcd值为4i的答案，因为压根就没有除4i外的 4i的倍数了
  * f[5i]同理
  * 但是f[2i]需要 - f[4i]才是gcd值为2i的答案
  * 执行f[2i] -= f[4i]，f[2i]现在是gcd值为2i的答案
  * 对于f[i]，其出现的倍数有2i,4i和5i，用f[i] - （f[2i] + f[4i] + f[5i]）
  * 可以发现 在求出原始定义的f[i]后
  * 只需要将i从大到小枚举，对于每个i，用f[i] -= f[j]， 其中 j = i, 2i, 3i ...
  * 即可算出gcd = i的路径数目，并且整个求和过程是调和级数求和 总的时间复杂度是 nlogn
  *
  * 接下来就是如何求f[i]
  * 在计算gcd为i的倍数的路径时，所有gcd(v,w)为 i的倍数 的边 都可以是路径的一部分
  * 这些边连通为一个分量，那么这个分量中的任意两点所表示的路径 gcd都是i的倍数
  * 用并查集求分量数目
  * 另外要注意 可以取 v = w, 也就是单点的情况，这种情况直接特殊处理
  * 其gcd为a[b], 可以为a[v]的因子对应的f贡献数目1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 15, M = 2e5;
int n, a[N], node1[N], node2[N], id[N], sz[N];
ll f[N];
vector<int> edges[N];

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return;
    id[p] = q, sz[q] += sz[p];
}

void solve() {
    // 因为原本的gcd(v,w)按因子拆分归类，在2e5内 因子个数最多不超过200
    // 因此即便是对于每个i，枚举gcd为其倍数的边 总共也不会超过200 * (n - 1)边
    for(int i = 1; i <= M; i++) {
        if(edges[i].empty()) continue;
        set<int> st;
        for(int& idx : edges[i])
            connect(node1[idx], node2[idx]);
        for(int& idx : edges[i]) {
            int p = find(node1[idx]), q = find(node2[idx]);
            if(!st.count(p)) st.insert(p), f[i] += (ll)sz[p] * (sz[p] - 1) / 2;
            if(!st.count(q)) st.insert(q), f[i] += (ll)sz[q] * (sz[q] - 1) / 2;
        }
        // 恢复并查集的初状态
        for(int& idx : edges[i]) {
            int v = node1[idx], w = node2[idx];
            sz[v] = sz[w] = 1, id[v] = v, id[w] = w;
        }
    }
    // 倒着将fi转换为答案
    for(int i = M; i >= 1; i--) {
        for(int j = 2 * i; j <= M; j += i)
            f[i] -= f[j];
    }
    for(int i = 1; i <= M; i++)
        if(f[i] > 0) cout << i << " " << f[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = i, sz[i] = 1;
        // 计算f时单个点的特殊处理
        for(int j = 1; j * j <= a[i]; j++) {
            if(a[i] % j == 0) {
                f[j]++;
                if(a[i] / j != j) f[a[i] / j]++;
            }
        }
    }
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        node1[i] = v, node2[i] = w;
        // 预处理gcd为i的倍数的边
        int t = gcd(a[v], a[w]);
        for(int j = 1; j * j <= t; j++) {
            if(t % j == 0) {
                edges[j].push_back(i);
                if(t / j != j) edges[t / j].push_back(i);
            }
        }
    }
    solve();
}