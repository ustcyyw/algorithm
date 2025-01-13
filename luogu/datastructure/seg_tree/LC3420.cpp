/**
 * @Time : 2025/1/12-5:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3420 数据结构 单调栈 线段树 和CF2009G2的做法有类似 ac代码需要改java
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5, MIN_VAL = -2e9;
int nxt[N], val[4 * N], idx[4 * N];
ll sum[N], suf[N];

#define ls x << 1
#define rs (x << 1) | 1

class Solution {
public:
    int n;
    vector<int> nums;
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        this->nums = nums;
        this->n = nums.size(), this->k = k;
        fill(idx, idx + 4 * n, 0), fill(val, val + 4 * n, MIN_VAL);
        for(int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
            add(i - 1, nums[i - 1]);
        }
        suf[n] = 0;
        stack<int> stack;
        for(int i = n - 1; i >= 0; i--) {
            while(!stack.empty() && nums[i] >= nums[stack.top()])
                stack.pop();
            nxt[i] = stack.empty() ? n : stack.top();
            stack.push(i);
            // [i, nxt[i] - 1]区间上的数都边成nums[i]
            suf[i] = suf[nxt[i]] + (ll)(nxt[i] - i) * nums[i] - (sum[nxt[i]] - sum[i]);
        }
        ll ans = 0;
        for(int i = 0, j = 0; i < n; i++) {
            while(j < n && cal(i, j) <= k)
                j++;
            ans += j - i;
        }
        return ans;
    }

    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v, idx[x] = pos;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = max(val[ls], val[rs]);
        if(val[x] == val[ls]) idx[x] = idx[ls];
        else idx[x] = idx[rs];
    }

    vector<int> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return {val[x], idx[x]};
        int mid = (l + r) >> 1;
        vector<int> res(2, MIN_VAL);
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) {
            vector<int> temp = search(rs, mid + 1, r, a, b);
            if(temp[0] > res[0]) res = temp;
        }
        return res;
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }
// 返回最小值所在的索引
    int search(int a, int b) {
        return search(1, 0, n, a, b)[1];
    }

    ll cal(int lo, int hi) {
        int j = search(lo, hi);
        return suf[lo] - suf[j] + (ll)(hi - j + 1) * nums[j] - (sum[hi + 1] - sum[j]);
    }
};
//
//import java.util.Arrays;
//import java.util.Stack;
//
//class Solution {
//    int n, k;
//    int[] nums, nxt, val, idx;
//    long[] sum, suf;
//    // 定义常量
//    static final int mod = 1000000007, N = 100005, MIN_VAL = (int) -2e9;
//
//public long countNonDecreasingSubarrays(int[] nums, int k) {
//        this.nums = nums;
//        n = nums.length;
//        this.k = k;
//        idx = new int[4 * n];
//        val = new int[4 * n];
//        Arrays.fill(val, MIN_VAL);
//        sum = new long[n + 1];
//        suf = new long[n + 1];
//        nxt = new int[n];
//        for (int i = 1; i <= n; i++) {
//            sum[i] = sum[i - 1] + nums[i - 1];
//            add(i - 1, nums[i - 1]);
//        }
//        suf[n] = 0;
//        Stack<Integer> stack = new Stack<>();
//        for (int i = n - 1; i >= 0; i--) {
//            while (!stack.isEmpty() && nums[i] >= nums[stack.peek()])
//                stack.pop();
//            nxt[i] = stack.isEmpty()? n : stack.peek();
//            stack.push(i);
//            // [i, nxt[i] - 1]区间上的数都变成 nums[i]
//            suf[i] = suf[nxt[i]] + (long) (nxt[i] - i) * nums[i] - (sum[nxt[i]] - sum[i]);
//        }
//        long ans = 0;
//        for (int i = 0, j = 0; i < n; i++) {
//            while (j < n && cal(i, j) <= k)
//                j++;
//            ans += j - i;
//        }
//        return ans;
//    }
//
//public void add(int x, int l, int r, int pos, int v) {
//        if (l == r) {
//            val[x] = v;
//            idx[x] = pos;
//            return;
//        }
//        int mid = (l + r) >> 1;
//        if (pos <= mid) add(x << 1, l, mid, pos, v);
//        else add((x << 1) | 1, mid + 1, r, pos, v);
//        val[x] = Math.max(val[x << 1], val[(x << 1) | 1]);
//        if (val[x] == val[x << 1]) idx[x] = idx[x << 1];
//        else idx[x] = idx[(x << 1) | 1];
//    }
//
//
//public int[] search(int x, int l, int r, int a, int b) {
//        if (a <= l && r <= b)
//            return new int[]{val[x], idx[x]};
//        int[] res = new int[2], temp;
//        int mid = (l + r) >> 1;
//        if (a <= mid)
//            res = search(x << 1, l, mid, a, b);
//        if (b > mid) {
//            temp = search((x << 1) | 1, mid + 1, r, a, b);
//            if (temp[0] > res[0]) res = temp;
//        }
//        return res;
//    }
//
//
//public void add(int pos, int v) {
//        add(1, 0, n, pos, v);
//    }
//
//    // 返回最小值所在的索引
//public int search(int a, int b) {
//        return search(1, 0, n, a, b)[1];
//    }
//
//public long cal(int lo, int hi) {
//        int j = search(lo, hi);
//        return suf[lo] - suf[j] + (long) (hi - j + 1) * nums[j] - (sum[hi + 1] - sum[j]);
//    }
//}