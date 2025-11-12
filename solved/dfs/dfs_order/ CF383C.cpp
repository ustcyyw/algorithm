/**
 * @Time : 2024/3/5-11:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : dfs序列 + 线段树区间修改
 */
/*
  * dfs序 同一个子树下的所有结点在dfs序下是连续的 将结点按dfs序排列出来
  * 对某个结点的操作1就是对一个连续区间进行查询
  * 对某个结点的操作2就是单点查询
  * 很适合使用线段树
  *
  * 但是对于操作1 区间上有的点是+val，有的点是-val 和结点所在的深度有关
  * 如果v的深度是偶数 其子结点w是偶数深度（只能是其孙结点、孙子的孙子结点...） 则+val，是奇数则-val
  * 如果v的深度是奇数 其子结点w是偶数深度则-val，是奇数则+val
  * 因此规定：如果v的深度是偶数 就进行区间+val的操作；如果v的深度是奇数 进行区间-val操作
  * 这样就使得
  * w深度是偶数时 w的值的变化与区间上的变化一致
  * w深度是奇数时 w的值的变化与区间上的变化相反
  */
#define ls x << 1
#define rs (x << 1) | 1
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int n, m, tt, points[N], depth[N], mp[N], cnt[N], tag[4 * N], val[4 * N];
vector<vector<int>> graph;

void dfs(int v, int f) {
    cnt[v] = 1, mp[v] = ++tt;
    if(f != -1) depth[v] = depth[f] + 1;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
        cnt[v] += cnt[w];
    }
}

void down(int x) {
    if(tag[x] == 0) return;
    tag[ls] += tag[x], tag[rs] += tag[x];
    val[ls] += tag[x], val[rs] += tag[x];
    tag[x] = 0;
}

void add(int x, int a, int b, int l, int r, int v) {
    if(a <= l && r <= b) {
        tag[x] += v, val[x] += v;
        return;
    }
    down(x);
    int mid = (l + r) >> 1;
    if(a <= mid) add(ls, a, b, l, mid, v);
    if(b > mid) add(rs, a, b, mid + 1, r, v);
    val[x] = val[ls] + val[rs];
}

int search(int x, int pos, int l, int r) {
    if(l == r) return val[x];
    down(x);
    int mid = (l + r) >> 1;
    if(pos <= mid) return search(ls, pos, l, mid);
    else return search(rs, pos, mid + 1, r);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    graph.assign(n + 1, {});
    fill(cnt, cnt + n + 1, 0);
    fill(tag, tag + 4 * n + 5, 0), fill(val, val + 4 * n + 5, 0);
    for(int i = 1; i <= n; i++)
        cin >> points[i];
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    depth[1] = 0, tt = 0, dfs(1, -1);
    for(int i = 1, type, x, v; i <= m; i++) {
        cin >> type >> x;
        if(type == 1) {
            cin >> v;
            if(depth[x] % 2 == 1) v = -v;
            int a = mp[x], b = a + cnt[x] - 1; // 根据dfs序确定区间操作的边界
            add(1, a, b, 1, n, v);
        } else {
            int ans = search(1, mp[x], 1, n);
            ans = (depth[x] % 2 == 1 ? -ans : ans) + points[x];
            cout << ans << "\n";
        }
    }
};