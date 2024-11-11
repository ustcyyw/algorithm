/**
 * @Time : 2024/5/27-4:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛131 t4
 */
 /*
  * 借用离线查询的思路 倒序来做
  * 对于操作1就是移除障碍物x，记其前一个障碍物为pre，后一个障碍物为next
  * 那么就会使得以pre开头的连续空位置长度变为 next - pre
  *
  * 对于操作2 [0,x]上的最长连续空位置
  * 1.x - pre
  * 2.在pre > 0的情况下 查询[0, pre - 1]上的最长连续空位置长度
  * 以上两种情况取最大
  *
  * 发现需要进行单点修改 也需要进行区间最大值查询 于是使用线段树
  * 为了维护x的前后障碍物pre next可以使用有序集合
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5, mod = 1e9 + 7;
#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

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
        val[x] = max(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MIN_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = max(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MIN_VAL);
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
    vector<bool> getResults(vector<vector<int>>& queries) {
        set<int> obs;
        obs.insert(0), obs.insert(N);
        for(auto& query : queries) {
            if(query[0] == 1)
                obs.insert(query[1]);
        }
        SegmentTree st(N);
        for(auto it = obs.begin(); *it != N; ) {
            int cur = *it, next = *(++it);
            st.add(cur, next - cur);
        }
        vector<bool> res;
        for(int i = queries.size() - 1; i >= 0; i--) {
            int x = queries[i][1];
            if(queries[i][0] == 1) {
                int pre = *(--obs.find(x)), next = *(++obs.find(x));
                st.add(pre, next - pre);
                obs.erase(x);
            } else {
                int sz = queries[i][2], pre = *(--obs.upper_bound(x));
                int t = pre > 0 ? st.search(0, pre - 1) : 0;
                int len = max(x - pre, t);
                res.push_back(len >= sz);
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};