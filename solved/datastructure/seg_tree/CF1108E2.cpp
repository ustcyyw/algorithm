/**
 * @Time : 2024/4/29-3:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1108E2 线段树 前后缀分解
 */
/*
 * 可以枚举最大值的下标 在确定最大值下标i的情况下
 * 任何包括i的区间操作都不应该 因为
 * 如果能取得答案的最小值也在这个区间内 那么最大值和最小值的差值不变
 * 如果能取得答案的最小值不在这个区间内 那么反而导致答案减小了
 * 那么其它区间操作肯定要都执行 因为最大值固定了 那么只要不影响最大值 让其它所有数变小有利
 */
#include<bits/stdc++.h>
using namespace std;
#define ls x << 1
#define rs (x << 1) | 1
typedef long long ll;
const int N = 1e5 + 5, mod = 998244353;
int n, m, nums[N], suf[N], val[4 * N], tag[4 * N];
vector<vector<int>> range;

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
    val[x] = min(val[ls], val[rs]);
}
// 查找区间上的最小值
int search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return val[x];
    down(x);
    int mid = (l + r) >> 1, res = 2e7;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
    return res;
}

void build(int x, int l, int r, int pos) {
    if(l == r) {
        val[x] = nums[pos];
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) build(ls, l, mid, pos);
    else build(rs, mid + 1, r, pos);
    val[x] = min(val[ls], val[rs]);
}

void build() {
    for(int i = 1; i <= n; i++)
        build(1, 1, n, i);
}

// 计算后缀
void init_suf() {
    build();
    sort(range.begin(), range.end());
    fill(suf, suf + n + 1, INT_MAX);
    for(int i = n, j = m - 1; i >= 1; i--) {
        while(j >= 0 && range[j][0] > i) {
            int l = range[j][0], r = range[j][1];
            add(1, 1, n, l, r, -1);
            j--;
        }
        suf[i] = search(1, 1, n, i, n);
    }
}

void solve() {
    init_suf();
    // 计算前缀的同时求出答案
    int ans = 0, mi = 1;
    sort(range.begin(), range.end(), [](auto &a, auto &b) -> bool {
        return a[1] < b[1];
    });
    build(), memset(tag, 0, sizeof(tag));
    for(int i = 1, j = 0; i <= n; i++) {
        while(j < m && range[j][1] < i) {
            int l = range[j][0], r = range[j][1];
            add(1, 1, n, l, r, -1);
            j++;
        }
        int pre = search(1, 1, n, 1, i);
        int temp = nums[i] - min(pre, suf[i]);
        if(temp > ans) ans = temp, mi = i;
    }
    cout << ans << "\n";
    vector<int> pick;
    for(auto& arr : range) {
        if(arr[0] > mi || arr[1] < mi) pick.push_back(arr[2]);
    }
    cout << pick.size() << "\n";
    for(int num : pick)
        cout << num << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    for(int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        range.push_back({l, r, i});
    }
    solve();
};