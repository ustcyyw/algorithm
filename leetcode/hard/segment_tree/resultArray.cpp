/**
 * @Time : 2024/3/3-12:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛387 t4
 */

/*
 * 要求大于某个数的元素个数 如果将数进行排序 就是其位置右边这个区间上有多少个元素
 * 将数添加到数组中的操作则是对单个位置的数量+1
 * 因此可以使用线段树
 */
#include<bits/stdc++.h>
using namespace std;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val; // 存储区域上的值

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
    unordered_map<int, int> map;
    vector<int> resultArray(vector<int>& nums) {
        map = scatter(nums);
        int m = map.size();
        SegmentTree tree1(m), tree2(m);
        vector<int> arr1, arr2;
        add(arr1, tree1, nums[0]), add(arr2, tree2, nums[1]);
        for(int i = 2; i < nums.size(); i++) {
            int lo = map[nums[i]] + 1;
            int c1 = tree1.search(lo, m), c2 = tree2.search(lo, m);
            if(c1 > c2 || (c1 == c2 && arr1.size() <= arr2.size())) add(arr1, tree1, nums[i]);
            else add(arr2, tree2, nums[i]);
        }
        for(int num : arr2) arr1.push_back(num);
        return arr1;
    }

    void add(vector<int>& arr, SegmentTree& tree, int num) {
        arr.push_back(num);
        tree.add(map[num], 1);
    }

    unordered_map<int, int> scatter(vector<int>& nums) {
        set<int> set;
        for(int num : nums)
            set.insert(num);
        unordered_map<int, int> map;
        for(int num : set)
            map[num] = map.size();
        map[INT_MAX] = map.size();
        return map;
    }
};