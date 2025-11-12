/**
 * @Time : 2023/12/14-10:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 要快速判断某个点a是否为b的祖先结点 想到dfs序
 * in[v], out[v] 分别表示遍历到v结点到时间戳、遍历完v及其所有子结点的时间戳
 * 如果 in[a] < in[b] < out[b] < out[a]， 那么a是b的祖先
 *
 * 本题查询的另外一个限制是最短路径的边数 由于是一颗树
 * 到某个点的最短路径唯一 就是沿着遍历的顺序走即可
 * 对最短路径的边数有要求，等价于遍历dfs的时候的深度
 * 在遍历的时候可以将同一深度的点放在同一个集合中，同一个深度的结点没有父子关系
 * 那么如果先遍历的结点x，然后遍历y，最后是z，则他们满足
 * in[x] < out[x] < in[y] < out[y] < in[z] < out[z]
 * 并且放入集合的顺序就是 x < y < z
 *
 * 对于某个查询q，到对应层级的结点集合中看 a要在b的最短路径上 即a是b的祖先（或者a就是b本身）
 * 要找到所有 in[a] <= in[b] < out[b] <= out[a] 的b
 * （等于号是特殊情况 即结点a和b是同一个）
 * 找到最小的 in[b1] 使得 in[a] <= in[b1] 成立
 * 找到最大的 out[b2] 使得 out[b2] <= out[a]成立
 * 那么在[b1, b2]上的b 都有 in[a] <= in[b] < out[b] <= out[a]。
 * 不在此区间上则，in[b] < in[a] or out[b] > out[a]， 总之a就不是他们的祖先结点了
 * 因此可以进行二分
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, q, tim, in[N], out[N];
vector<vector<int>> graph, outArr, inArr;

void dfs(int v, int depth) {
    in[v] = ++tim;
    inArr[depth].push_back(tim);
    for(int w : graph[v])
        dfs(w, depth + 1);
    out[v] = ++tim;
    outArr[depth].push_back(tim);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    graph.assign(n + 1, {});
    inArr.assign(n + 1, {}), outArr.assign(n + 1, {});;
    for(int i = 2, f; i <= n; i++) {
        cin >> f;
        graph[f].push_back(i);
    }
    dfs(1, 0);
    cin >> q;
    for(int i = 0, f, depth; i < q; i++) {
        cin >> f >> depth;
        int lo = lower_bound(inArr[depth].begin(), inArr[depth].end(), in[f]) - inArr[depth].begin();
        int hi = upper_bound(outArr[depth].begin(), outArr[depth].end(), out[f]) - outArr[depth].begin();
        cout << max(0, hi - lo) << endl;
    }
}