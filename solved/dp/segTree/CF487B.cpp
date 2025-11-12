/**
 * @Time : 2023/12/10-4:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 要查找区间上的最大值和最小值 想到了线段树
 * dp[i]：截止i元素 并且满足题目要求的子数组拆分最小次数
 * 看dp[i]可以从什么地方进行转移
 * 首先要保证以i为结尾的子数组的长度 >= l，那么该子数组的左端点下标应该 <= rt = i - l + 1
 * 左端点下标越往左，子数组最大值和最小值之差越可能超过s，因此有单调特性
 * 可以二分左端点下标的最小值 二分的范围是 [1, rt + 1], 二分答案的结果以lo表示
 * 如果取到了rt + 1 说明以i为结尾是拆不出满足题意的子数组的
 * 否则可以拆分的子数组的左端点下标范围是[lo, rt]， 那么前置子数组的右端点是[lo - 1, rt - 1]
 * 所以dp[i] = max{dp[j], j 属于 [lo - 1, rt - 1]} + 1
 * 这里又是一个区间上取最大值，用线段树进行dp优化
 */

#include<bits/stdc++.h>
using namespace std;

#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;
int n, l, s, ans = MAX_VAL;

class SegmentTree {
private:
    int n;
    vector<int> val; // 存储区域上的最小值

    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = min(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MAX_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s >> l;
    SegmentTree maxTree(n), minTree(n), tree(n);
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        maxTree.add(i, -num), minTree.add(i, num);
    }
    tree.add(0, 0); // 边界条件 空数组的拆分次数是0
    for(int i = l; i <= n; i++) { // 第一个分组的结尾元素至少是第l个元素
        int rt = i - l + 1, lo = 1, hi = rt + 1;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            int v1 = maxTree.search(mid, i), v2 = minTree.search(mid, i);
            if(-v1 - v2 > s) lo = mid + 1;
            else hi = mid;
        }
        if(lo != rt + 1) {
            ans = tree.search(lo - 1, rt - 1) + 1;
            tree.add(i, ans);
        }
    }
    cout << (ans >= MAX_VAL ? -1 : ans) << endl;
}