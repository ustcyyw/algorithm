/**
 * @Time : 2024/3/26-11:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
  * 区间操作 还要找最大值 考虑到时间复杂度 线段树 关键是维护什么
  * 答案是最长上升序列（相等视为上升） 那么这是一个要维护的信息
  * 但是操作会使区间上的4和6翻转，那么最长上升序列（前面4很多、后面7很多）就会变成最长下降子序列
  * 因此这也是一个要维护的信息
  * 在上升序列前面加上4，或者后面加上7 依旧是上升序列
  * 在下降序列后面加上4，或者前面加上7 依旧是下降序列
  * 因此区间上4和7的个数也需要维护
  */
#define ls x << 1
#define rs (x << 1) | 1
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
int n, m, four[4 * N], seven[4 * N], tag[4 * N], inc[4 * N], decs[4 * N];
string s, type;

void update(int x) {
    four[x] = four[ls] + four[rs];
    seven[x] = seven[ls] + seven[rs];
    inc[x] = max(four[ls] + inc[rs], inc[ls] + seven[rs]);
    decs[x] = max(seven[ls] + decs[rs], decs[ls] + four[rs]);
}

void build(int x, int l, int r) {
    if(l == r) {
        four[x] = s[l] == '4', seven[x] = s[l] == '7';
        decs[x] = inc[x] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    update(x);
}

void exch(int x) {
    swap(four[x], seven[x]);
    swap(inc[x], decs[x]);
}

void down(int x) {
    if(tag[x] == 0) return;
    tag[ls] += tag[x], tag[rs] += tag[x];
    if(tag[x] % 2 == 1) exch(ls), exch(rs);
    tag[x] = 0;
}

void add(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        tag[x]++, exch(x);
        return;
    }
    down(x);
    int mid = (l + r) >> 1;
    if(a <= mid) add(ls, l, mid, a, b);
    if(b > mid) add(rs, mid + 1, r, a, b);
    update(x);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    cin >> s;
    memset(tag, 0, sizeof(tag));
    build(1, 0, n - 1);
    for(int i = 1, l, r; i <= m; i++) {
        cin >> type;
        if(type == "count") cout << inc[1] << "\n";
        else {
            cin >> l >> r;
            add(1, 0, n - 1, l - 1, r - 1);
        }
    }
};
