/**
 * @Time : 2024/11/13-12:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 最多选择m个数修改 修改幅度为[-k,k]
1.如果某个数a不修改（可以不操作 或者操作 + 0）且以它为频率最高数
那么m次操作 应该尽可能全用上 将 [a - k, a + k] 内的所有数变为a
cnt[a - k, a + k] - cnt[a]: 需要修改的数
所以其实能变化的数的数量  min(m, cnt[a - k, a + k] - cnt[a])
2.答案是某个原本不在数组中的数 b
围绕着答案b，要将[b - k, b + k] 内的所有数变为b
假设 大于b - k的数组中原本的最小数是c 那么这个答案实际上是将[c, b + k]内的数变为了b
[b - k, c - 1]这个区间没有任何数，那完全可以将区间向右移动一点 变为[c, c + 2k] 结果至少不会更差

  因此 可以成为答案的数一定是原数组中的数 或者原数组中的数+k
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<ll> val;
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
        if (a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if (a <= mid) res = search(ls, l, mid, a, b);
        if (b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0ll);
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
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        vector<ll> arr, pos;
        for(int num : nums) {
            arr.push_back(num), arr.push_back(num - k);
            arr.push_back(num + k), arr.push_back((ll)num + 2 * k);
        }
        pos = scatter(arr);
        SegmentTree tree(pos.size());
        unordered_map<int, int> map;
        for(int num : nums) {
            int idx = find(pos, num);
            map[idx]++, tree.add(idx, 1);
        }
        int ans = 0;
        for(int num : nums) {
            // 以num为最高频率的元素
            int idx = find(pos, num), lo = find(pos, num - k), hi = find(pos, num + k);
            int c1 = idx - 1 >= lo ? tree.search(lo, idx - 1) : 0;
            int c2 = idx - 1 >= lo ? tree.search(idx + 1, hi) : 0;
            ans = max(ans, map[idx] + min(numOperations, c1 + c2));
            // 以num + k为最高频率的元素
            int c3 = tree.search(idx, find(pos, (ll)num + 2 * k));
            ans = max(ans, min(numOperations, c3));
        }
        return ans;
    }

    vector<ll> scatter(vector<ll>& num) {
        vector<ll> pos = num;
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        return pos;
    }

    int find(vector<ll>& pos, ll val) {
        return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
    }
};