/**
 * @Time : 2024/3/16-2:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 逆向思维：
 * 直接求中位数为m的子数组不好求，但是可以反过来想
 * 先求中位数 >= m的子数组，再求中位数 >= m+1的子数组。二者做差就是答案
 * (类似于数位dp时 求约束了最大值的好求，求约束最小值和最大值的不好求
 * 那就求单边 求 < 最小值的答案，和 <= 最大值的答案 做差)
 * 于是在指定m的情况下，数组中的数被分为两类 类似于easy版本中一样
 * pos：值 >= m的元素数量
 * neg：值 < m的元素数量
 * 要使子数组中位数>=m，就要求 pos - neg >= 1
 * pos[j] - pos[i] - (neg[j] - neg[i]) >= 1
 * pos[j] - neg[j] - (pos[i] - neg[i]) >= 1
 * diff[i] <= diff[j] - 1
 * 要求区间上的和 并且涉及单点修改 线段树
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int T = 2e5, N = 2e5 + 5;
ll n, m, nums[N];

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val; // 存储区域上的和

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

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

// 找到中位数大于等于k的子数组的数量
ll solve(int k) {
    SegmentTree tree(N * 4);
    tree.add(0 + T, 1);
    ll cnt = 0, pos = 0, neg = 0;
    for(int i = 1; i <= n; i++) {
        pos += nums[i] >= k, neg += nums[i] < k;
        int diff = pos - neg;
        if(diff - 1 + T >= 0) cnt += tree.search(0, diff - 1 + T);
        tree.add(diff + T, 1);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    cout << (solve(m) - solve(m + 1)) << "\n";
};