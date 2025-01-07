/**
 * @Time : 2024/5/27-10:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P4513 线段树 区间子数组问题
 */
/*
 * sum: 区间和
 * ms:区间上的非空最大子数组和
 * sumL:区间上包括了左端点的最大子数组和
 * sumR:区间上包括了右端点的最大子数组和
 *
 * 类似题目
 * https://leetcode.cn/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/
 * https://www.luogu.com.cn/problem/P3097
 * https://codeforces.com/problemset/problem/1906/F
 * https://leetcode.cn/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/description/
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
int T, n, m, sum[4 * N], sumL[4 * N], sumR[4 * N], ms[4 * N];
#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;
void update(int x) {
    sum[x] = sum[ls] + sum[rs];
    // 如果最大子数组和没有跨mid max(ms[ls], ms[rs]); 最大子数组和跨越了mid sumL[rs] + sumR[ls]
    ms[x] = max({ms[ls], ms[rs], max(sumL[rs], 0) + sumR[ls], sumL[rs] + max(0, sumR[ls])});
    sumR[x] = max(sumR[rs], sum[rs] + max(0, sumR[ls]));
    sumL[x] = max(sumL[ls], sum[ls] + max(0, sumL[rs]));
}

void add(int x, int l, int r, int pos, int v) {
    if(l == r) { // 这里是单点修改 不是单点加减
        sum[x] = sumL[x] = sumR[x] = v, ms[x] = v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, pos, v);
    else add(rs, mid + 1, r, pos, v);
    update(x);
}

vector<int> search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return {sum[x], sumL[x], sumR[x], ms[x]};
    int mid = (l + r) >> 1;
    vector<int> res(4, MIN_VAL);
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) {
        if(res[0] != MIN_VAL) {
            vector<int> aux(4, 0), rt = search(rs, mid + 1, r, a, b);
            aux[0] = res[0] + rt[0];
            // sumL[x] = max(sumL[ls], sum[ls] + max(0, sumL[rs]));
            aux[1] = max(res[1], res[0] + max(0, rt[1]));
            // sumR[x] = max(sumR[rs], sum[rs] + max(0, sumR[ls]));
            aux[2] = max(rt[2], rt[0] + max(0, res[2]));
            aux[3] = max({res[3], rt[3],
                          max(rt[1], 0) + res[2], rt[1] + max(0, res[2])});
            swap(res, aux);
        } else res = search(rs, mid + 1, r, a, b);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        add(1, 1, n, i, num);
    }
    for(int i = 1, t, n1, n2; i <= m; i++) {
        cin >> t >> n1 >> n2;
        if(t == 1) {
            if(n1 > n2) swap(n1, n2);
            cout << search(1, 1, n, n1, n2)[3] << "\n";
        } else add(1, 1, n, n1, n2);
    }
};