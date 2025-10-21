/**
 * @Time : 2025/10/20-21:18
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3721 2766 思维 线段树 线段树二分 <套路>重复元素处理
 */
#include<bits/stdc++.h>
/*
    * 1.参考P1972，从左往右枚举右端点i的时候，动态维护前缀和，可以计算不重复元素的数量
    * 本题中不重复元素还分奇数、偶数
    * 2.如果只是问子数组中奇数和偶数数量相等的最大子数组，就可以将偶数视为+1，奇数视为-1
    * 通过前缀和sum[l] = sum[r]即可判断出[l+1,r]这个子数组中奇数和偶数数量相等
    *
    * 将上述两个思路结合起来，用重复元素处理的套路维护前缀和sum_change，然后对于任意的i
    * 去找最小的j使得 sum_change[i] = sum_change[j]
    *
    * 动态维护sum_change，但是从暴力计算的角度来看，有效奇数是-1，有效偶数是1，无效的数是0
    * 那么sum_change相邻两个位置的值，差距最多是1
    * 比如数组 [3,1,1,2,3,2,1]
    * i = 5: [*,*,1,*,3,2,*]，对应的sum_change为[0,0,0,-1,-1,-2,-1,-1]
    * 差距最多是1，那么值就是连续的，也就是说区间[l,r]上的最大值maxV，最小值minV
    * 只要满足 maxV >= sum_change[i] >= minV, 在区间上就一定存在j使得 sum_change[i] = sum_change[j]
    * 那么要找最小的j使得要求成立，等价于找[0,i]上最靠左的区间使得maxV >= sum_change[i] >= minV
    *
    * 线段树 可以维护区间加，也可以维护最大值最小值 在线段树上二分去确定区间
    */
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31, N = 1e5 + 5;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> minV, maxV, val, tag;

    int find(int x, int l, int r, int v) {
        if(v > maxV[x] || v < minV[x]) return -1;
        if(l == r) return l;
        down(x);
        int mid = (l + r) >> 1;
        int temp = find(ls, l, mid, v);
        if(temp != -1) return temp;
        return find(rs, mid + 1, r, v);
    }

    int search(int x, int l, int r, int pos) {
        if(l == r) return val[x];
        down(x);
        int mid = (l + r) >> 1;
        if(pos <= mid) return search(ls, l, mid, pos);
        else return search(rs, mid + 1, r, pos);
    }

    void down(int x) {
        if(tag[x] == 0) return;
        val[ls] += tag[x], val[rs] += tag[x];
        minV[ls] += tag[x], minV[rs] += tag[x];
        maxV[ls] += tag[x], maxV[rs] += tag[x];
        tag[ls] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
    }

    // 区间修改
    void add(int x, int l, int r, int a, int b, int v) {
        if(a <= l && r <= b) {
            minV[x] += v, maxV[x] += v, val[x] += v, tag[x] += v;
            return ;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(a <= mid) add(ls, l, mid, a, b, v);
        if(b > mid) add(rs, mid + 1, r, a, b, v);
        minV[x] = min(minV[ls], minV[rs]);
        maxV[x] = max(maxV[ls], maxV[rs]);
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        minV = vector(4 * (n + 1), 0);
        maxV = vector(4 * (n + 1), 0);
        val = vector(4 * (n + 1), 0);
        tag = vector(4 * (n + 1), 0);
    }

    void add(int l, int r, int v) {
        add(1, 0, n, l, r, v);
    }

    int search(int pos) {
        return search(1, 0, n, pos);
    }

    int find(int v) {
        return find(1, 0, n, v);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        SegmentTree st(n);
        unordered_map<int, int> pre;
        for(int i = 1; i <= n; i++) {
            int num = nums[i - 1], v = num % 2 == 0 ? 1 : -1, rv = -1 * v;
            if(!pre.count(num)) st.add(i, n, v);
            else st.add(pre[num], i - 1, rv);
            pre[num] = i;
            int j = st.find(st.search(i));
            if(j != -1) ans = max(ans, i - j);
        }
        return ans;
    }
};