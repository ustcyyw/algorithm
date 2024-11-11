/**
 * @Time : 2024/6/16-5:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛402 t4 线段树
 */
#include<bits/stdc++.h>
using namespace std;
#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
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

    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        SegmentTree tree(n);
        for(int i = 1; i < n - 1; i++) {
            if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
                tree.add(i, 1);
        }
        vector<int> res;
        for(auto& q : queries) {
            int t = q[0], x = q[1], y = q[2];
            if(t == 1) {
                int cnt = tree.search(x, y);
                if(check(nums, x)) cnt--;
                if(x != y && check(nums, y)) cnt--;
                res.push_back(cnt);
            } else {
                nums[x] = y;
                tree.add(x, check(nums, x));
                if(x > 0) tree.add(x - 1, check(nums, x - 1));
                if(x < n - 1) tree.add(x + 1, check(nums, x + 1));
            }
        }
        return res;
    }

    int check(vector<int>& nums, int x) {
        if(x == 0 || x == nums.size() - 1) return 0;
        if(nums[x] > nums[x - 1] && nums[x] > nums[x + 1])
            return 1;
        return 0;
    }
};
