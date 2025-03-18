/**
 * @Time : 2025/3/17-10:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF845G 2300 线性基 trick （看答案学习）
 */
 /*
  * 和P4151是同一个题 只需要注意输入的范围 以及将min函数改成max函数即可
  */
/*
  * 先假设找到一条 1 -> n 的路径 称为初始链
  * 初始链上会有很多分枝条
  * 如果这些分枝条不在任何环中 那么走过去还得原路走回来 所以不用考虑
  * 只考虑这些分枝在环中 或者连接了别的环
  *
  * 1. 分枝连接了别的环 那么就可以考虑从这个枝走到环中 绕环一周再回来
  * 这个枝条走了两遍，因此整个路径的异或值是 初始链 xor 环
  * 会有多个这样的分枝 那么这些分枝条连着的环 都是独立的可选可不选
  * 注意：
  * 1.1 分枝连接着的环 可能是嵌套的环（几个环共用一些边）的复杂情况
  * 但是这种嵌套的环 选择了其中的几个 将公共边去掉 还是等价于选了某一个环
  * 多个环异或 = 另外一个环 就说明他们是等价的 就视为选了那个单一环即可
  * 1.2 可能分枝上的环 又长更多分枝 又连接着别的环 同理 这些环一样是独立可选可不选
  *
  * 2. 分枝绕了一个环直接又回到初始链 也就是初始链有一部分在环中
  * 如果要选择这个环 就相当于换了一条初始链 选择了这个环中的另一部分
  * 等价于用初始链异或上该环
  * 这就解释了为什么可以任意先找到 1 -> n 的路径
  * 因为最终答案选出来的那条路径 总是可以通过一开始任意找的路径 通过异或一些环来换到最佳路径
  *
  * 综上 所做的事情就是 选择任意个环 来使路径的异或值最小
  * 选择任意个环，就可以从这些环的集合的角度考虑 在其线性基中选择与在原集合选择是等价的
  * 但是线性基的一个性质就是 可以找到异或的最大值/最小值
  *
  * trick 通过dfs找到独立的环（异或空间的基）的异或值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, M = 63;
ll T, n, m, basis[M + 1], path[N], marked[N];
vector<vector<ll>> graph[N];

void insert(ll num) {
    for(int i = M; i >= 0; i--) {
        if(num >> i == 1) {
            if(basis[i] == 0) {
                basis[i] = num;
                break;
            } else num ^= basis[i];
        }
    }
}

void dfs(int v, int f, ll val) {
    path[v] = val, marked[v] = 1;
    for(auto& edge : graph[v]) {
        ll w = edge[0], t = edge[1];
        if(w == f) continue;
        if(marked[w]) insert(path[w] ^ val ^ t);
        else dfs(w, v, val ^ t);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1, a, b, w; i <= m; i++) {
            cin >> a >> b >> w;
            graph[a].push_back({b, w}), graph[b].push_back({a, w});
        }
        dfs(1, -1, 0);
        ll ans = path[n];
        for(int i = M; i >= 0; i--)
            ans = min(ans, ans ^ basis[i]);
        cout << ans;
    }
}