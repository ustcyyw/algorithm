/**
 * @Time : 2024/5/27-3:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P3097 线段树 区间子序列问题
 */
 /*
  * 类似题目
  * https://www.luogu.com.cn/problem/P4513
  * https://leetcode.cn/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
#define ls x << 1
#define rs (x << 1) | 1
int T, n, d;
// 分别是[], [), (], ()区间上的最大子序列和
vector<vector<ll>> sum;

void update(int l, int r, vector<ll>& arr, vector<ll>& left, vector<ll>& right) {
    if(l + 1 == r) {
        arr[0] = 0, arr[3] = 0;
        arr[1] = left[0], arr[2] = right[0];
    } else {
        arr[0] = max({left[1] + right[2], left[0] + right[2], left[1] + right[0]});
        arr[1] = max({left[0] + right[3], left[1] + right[1], left[1] + right[3]});
        arr[2] = max({left[3] + right[0], left[3] + right[2], left[2] + right[2]});
        arr[3] = max({left[2] + right[3], left[3] + right[1], left[3] + right[3]});
    }
}

vector<ll> search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return sum[x];
    int mid = (l + r) >> 1;
    vector<ll> res(4, LONG_LONG_MIN);
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) {
        if(res[0] != LONG_LONG_MIN) {
            vector<ll> aux(4, 0ll), rt = search(rs, mid + 1, r, a, b);
            update(l, r, aux, res, rt);
            swap(res, aux);
        } else res = search(rs, mid + 1, r, a, b);
    }
    return res;
}

void add(int x, int l, int r, int pos, int v) {
    if(l == r) {
        sum[x][0] = max(0, v);
        return ;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, pos, v);
    else add(rs, mid + 1, r, pos, v);
    update(l, r, sum[x], sum[ls], sum[rs]);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> d;
    sum.assign(4 * n + 8, vector(4, 0ll));
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        add(1, 1, n, i, num);
    }
    ll ans = 0;
    for(int i = 1, pos, val; i <= d; i++) {
        cin >> pos >> val;
        add(1, 1, n, pos, val);
        vector<ll> temp = search(1, 1, n, 1, n);
        ll mv = 0;
        for(ll v : temp)
            mv = max(mv, v);
        ans = ans + mv;
    }
    cout << ans;
};