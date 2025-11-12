/**
 * @Time : 2024/3/22-4:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 枚举z模式中的左下端点p(x2, y2)
  * 假设正方形右上边界的坐标是q(x1, y1)
  * 那么正方形边长为 x2 - x1 + 1
  * 并且记left为q及其左边连续的z的长度，right为p及其右边边连续的z的长度，l为p所在对角线右上连续的z的长度
  * 要让这个正方形符号条件 就要求
  * left >= x2 - x1 + 1, 也就是 x2 <= left + x1 - 1
  * 并且 min(l, right) >= x2 - x1 + 1，也就是 x1 >= x2 - min(l, right) + 1
  *
  * 1.在枚举的过程中 不断记录 {left + x1 - 1, x1}
  * 随着x2的增大，要求left + x1 - 1增大，将不满足x2 <= left + x1 - 1的值剔除
  * 这样就保证了留在集合中的元素保障了上边界满足要求
  *
  * 2.然后在这样的集合中找到所有满足 >= x2 - min(l, right) + 1 的x1
  * 涉及到区间和的查找 使用线段树
  * 而1中添加到集合与从集合删除 就是单点修改+1、-1
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 3005, MOD = 1e9 + 7;
int n, m, pre[N][N], suf[N][N], val[N * 4];
string grid[3005];

#define ls x << 1
#define rs (x << 1) | 1

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

void init() {
    for(int i = 0; i < n; i++) {
        for(int j = 0, len = 0; j < m; j++) {
            len = grid[i][j] == 'z' ? len + 1 : 0;
            pre[i][j] = len;
        }
        for(int j = m - 1, len = 0; j >= 0; j--) {
            len = grid[i][j] == 'z' ? len + 1 : 0;
            suf[i][j] = len;
        }
    }
}

void solve() {
    init();
    ll ans = 0;
    for(int k = 0; k <= m + n - 2; k++) { // 枚举每条对角线
        memset(val, 0, sizeof(val));
        multimap<int, int> map;
        for(int i = max(0, k - m + 1), j = k - i, l = 0; i < n && j >= 0; i++, j--) {
            map.insert({pre[i][j] + i - 1, i});
            add(1, 0, n - 1, i, 1);
            while(!map.empty() && i > map.begin()->first) {
                int x = map.begin()->second;
                add(1, 0, n - 1, x, -1);
                map.erase(map.begin());
            }
            l = grid[i][j] == 'z' ? l + 1 : 0;
            int temp = min(suf[i][j], l);
            ans += search(1, 0, n - 1, max(0, i - temp + 1), n - 1);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> grid[i];
    solve();
};