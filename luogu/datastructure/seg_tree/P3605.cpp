/**
 * @Time : 2024/3/27-2:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 线段树的运用
 */
 /*
  * 对于树中结点x，找到以x为根的子树中有多少个结点权值小于x
  * 对于所有结点都求上述问题的答案
  * 可以使用线段树来维护 查找大于某个值的区间上有多少个数
  * 在dfs中 遍历x的子树之前查询一次，记为cnt1
  * 在遍历x的子树完成之后查询一次，记为cnt2
  * 那么 cnt2 - cnt1 就是x的子树中大于x权值的点的数量
  */
#define ls x << 1
#define rs (x << 1) | 1
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, p[N], val[4 * N], ans[N];
vector<int> graph[N];
unordered_map<int, int> mp;

void add(int x, int l, int r, int pos, int v) {
    if(l == r) {
        val[x] += v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, pos, v);
    else add(rs, mid + 1, r, pos, v);
    val[x] = val[ls] + val[rs];
}

int search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return val[x];
    int mid = (l + r) >> 1, res = 0;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) res += search(rs, mid + 1, r, a, b);
    return res;
}

void dfs(int v, int f) {
    add(1, 1, n, mp[p[v]], 1);
    int cnt1 = search(1, 1, n, mp[p[v]], n);
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
    }
    int cnt2 = search(1, 1, n, mp[p[v]], n);
    ans[v] = cnt2 - cnt1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    set<int> set;
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
        set.insert(p[i]);
    }
    mp.clear();
    for(int num : set)
        mp[num] = (int)mp.size() + 1;
    memset(graph, {}, sizeof(graph));
    for(int i = 2, v; i <= n; i++) {
        cin >> v;
        graph[v].push_back(i);
    }
    dfs(1, -1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << "\n";
};