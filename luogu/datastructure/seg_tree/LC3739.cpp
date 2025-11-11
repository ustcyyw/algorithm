/**
 * @Time : 2025/11/10-10:10
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3739 2093 前缀和 线段树
 */
 /*
  * 将target视为1，其它数视为-1，那么满足sum[i] - sum[j] >= 1 就能保证nums[j+1,i]子数组上target超过一半
  * sum[j] <= sum[i] - 1，枚举i的时候 找满足条件的j 就是一个区间上的和查询
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val, tag, cnt;
    // 单点修改
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

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size(), sum = 0, m = n + 5;
        SegmentTree st(2 * m);
        st.add(m, 1);
        ll ans = 0;
        for(int num : nums) {
            sum += num == target ? 1 : -1;
            ans += st.search(0, sum - 1 + m);
            st.add(sum + m, 1);
        }
        return ans;
    }
};