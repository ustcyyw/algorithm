/**
 * @Time : 2024/3/25-12:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 枚举区间左端点lo lo右边出现过的数字num
  * 记录它最靠近lo的位置l和次靠近lo的位置r 以及次次靠近lo的位置nr
  * 那么对于lo这个左端点 [l, r - 1]是一个该数字可行的右端点区间
  * [r, nr]是一个该数字不可行的右端点区间
  * 对于所有lo右端的数字 [li, ri - 1]，将这些区间合并
  *
  * 可以将区间上的值+1来表示当前数字使得该区间是可选的，区间上的值-1来表示当前数字使得该区间不可选的
  * 那么值大于0的点就是一个可选的右端点
  * 区间修改 并且查询区间[lo, n - 1]上为0的点有多少个，可选右端点数量就是 n - lo - zero[lo, n - 1]
  * 可以用线段树维护区间上的最小值、区间上最小值的数量。
  * 注意 如果区间上的最小值是0，那么当前左端点贡献的答案是 n - lo - zero[lo, n - 1]
  * 如果区间上的最小值是1，那么[lo, n - 1]上所有点都是可选右端点 答案贡献 n - lo
  */
#include<bits/stdc++.h>
#define ls x << 1
#define rs (x << 1) | 1
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int n, nums[N], nxt[N], nn[N], tag[4 * N], mv[4 * N], cnt[4 * N];

void build(int x, int l, int r) { // 初始化cnt
    if(l == r) {
        cnt[x] = 1;
        return;
    }
    cnt[x] = r - l + 1;
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
}

void update(int x) {
    if(mv[ls] == mv[rs]) {
        cnt[x] = cnt[ls] + cnt[rs];
        mv[x] = mv[rs];
    } else {
        if(mv[ls] < mv[rs]) mv[x] = mv[ls], cnt[x] = cnt[ls];
        else mv[x] = mv[rs], cnt[x] = cnt[rs];
    }
}

void down(int x) {
    if(tag[x] == 0) return;
    tag[ls] += tag[x], tag[rs] += tag[x];
    mv[ls] += tag[x], mv[rs] += tag[x];
    tag[x] = 0;
}

void add(int x, int l, int r, int a, int b, int v) {
    if(a <= l && r <= b) {
        tag[x] += v, mv[x] += v;
        return;
    }
    down(x);
    int mid = (l + r) >> 1;
    if(a <= mid) add(ls, l, mid, a, b, v);
    if(b > mid) add(rs, mid + 1, r, a, b, v);
    update(x);
}

pair<int, int> search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return {mv[x], cnt[x]};
    down(x);
    int mid = (l + r) >> 1;
    pair<int, int> p = {INT_MAX, 0};
    if(a <= mid) p = search(ls, l, mid, a, b);
    if(b > mid) {
        pair<int, int> temp = search(rs, mid + 1, r, a, b);
        if(temp.first < p.first) p = temp;
        else if(temp.first == p.first) p.second += temp.second;
    }
    return p;
}

void solve() {
    ll ans = 0;
    for(int i = n; i >= 1; i--) {
        int num = nums[i];
        add(1, 1, n, i, nxt[num] - 1, 1);
        if(nxt[num] != n + 1) add(1, 1, n, nxt[num], nn[num] - 1, -1);
        pair<int, int> p = search(1, 1, n, i, n);
        if(p.first > 0) ans += n - i + 1;
        else ans += n - i + 1 - search(1, 1, n, i, n).second;
        nn[num] = nxt[num];
        nxt[num] = i;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    memset(tag, 0, sizeof(tag)), memset(mv, 0, sizeof(mv));
    build(1, 1, n);
    fill(nn, nn + n + 1, n + 1), fill(nxt, nxt + n + 1, n + 1);
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};