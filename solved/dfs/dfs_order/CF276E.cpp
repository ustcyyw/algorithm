/**
 * @Time : 2025/1/1-4:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF276E 2100 dfs序 线段树
 */
 /*
  * 除了root，其它结点的度数最多为2 也就是说其它结点最多有一个子结点
  * 形象地描述就是 除了根结点 其它树枝上不会分叉
  * 那么对于操作0来说，从v结点向下延伸只在一条树枝上延伸
  * 从v结点向上延伸 也是在一条树枝上延伸
  * 如果能走到root，那么会将root向下固定距离的结点都覆盖
  *
  * 所以实际上修改的结点分为两部分
  * 1. 与root距离为一个定值dis的结点
  * 2. v这条树枝上与v距离为d以内的结点
  * 这两部分会有重叠，但是重叠部分归结到1中
  * 对于第一部分的处理 就是深度[0, dis]上的结点都+x，转化为对深度的范围加法
  * 第二部分则转化为dfs序上的区间加法
  * 麻烦的点在于确定第二部分的区间范围
  *
  * 查询操作则是 深度上叠加的值 + dfs序上叠加的值
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, q, tim = 0, depth[N], cnt[N], dfn[N];
vector<vector<int>> graph;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag;
    int search(int x, int l, int r, int a) {
        if(l == r) return val[x];
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) return search(ls, l, mid, a);
        return search(rs, mid + 1, r, a);
    }
    // 区间修改操作中的下传函数
    void down(int x) {
        if(tag[x] == 0) return;
        val[ls] += tag[x], val[rs] += tag[x];
        tag[ls] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
    }
    // 区间修改
    void add(int x, int l, int r, int a, int b, int v) {
        if(a <= l && r <= b) {
            val[x] += v, tag[x] += v;
            return ;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) add(ls, l, mid, a, b, v);
        if(b > mid) add(rs, mid + 1, r, a, b, v);
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
        tag = vector(4 * (n + 1), 0);
    }

    void add(int a, int b, int v) {
        add(1, 0, n, a, b, v);
    }

    int search(int a) {
        return search(1, 0, n, a);
    }
};

void dfs(int v, int f, int layer) {
    depth[v] = layer, dfn[v] = tim++, cnt[v] = 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v, layer + 1);
        cnt[v] += cnt[w];
    }
}

SegmentTree layerTree(N), dfsTree(N);

int findDown(int v, int d) {
    int t = min(cnt[v] - 1, d);
    return dfn[v] + t;
}

int findUp(int v, int d) {
    if(depth[v] > d) return dfn[v] - d;
    int more = d - depth[v];
    return dfn[v] - (depth[v] - more - 1); // 要注意重叠的部分
}

void add(int v, int x, int d) {
    int moreLayer = d - depth[v];
    if(moreLayer >= 0) layerTree.add(0, moreLayer, x);
    int lo = findUp(v, d), hi = findDown(v, d);
    if(lo <= hi) dfsTree.add(lo, hi, x);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> q;
        graph.assign(n + 1, {});
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(1, -1, 0);
        for(int i = 1, type, v, x, d; i <= q; i++) {
            cin >> type >> v;
            if(type == 0) {
                cin >> x >> d;
                add(v, x, d);
            } else cout << layerTree.search(depth[v]) + dfsTree.search(dfn[v]) << "\n";
        }
    }
};