/**
 * @Time : 2024/12/11-8:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3382 线段树 排序 思维
 */
 /*
  * 矩阵的中间和边不允许有其它点 那么矩阵的四个顶点 必须是相邻的
  * 枚举矩形的右边 就需要先按y坐标分组 枚举相邻的两个点
  * (x1, y), (x2, y) 然后这两个点分别向左找相邻的两个点(x1, y1), (x2, y2)
  * 这里不仅要能找到前置点 并且要求 y1 == y2
  * 所以也要按x坐标进行分组 这样方便查找
  * 这样就保证了找到一个右边及上下边没有其它结点的矩阵 还得确定矩形左边及内部是否有结点
  * 由于是枚举矩形的右边 此时已经考虑过的点都在y这条线左边
  * 并且要考虑的是[x1 + 1, x2 - 1]这个x坐标范围内
  * 如果有一个点(x3,y3)在矩阵内部，那么它满足 x3属于[x1 + 1, x2 - 1] 且 y3 >= y1
  * 如果所有点都不在矩阵内，就要求对于所有x3属于[x1 + 1, x2 - 1]的结点都有 y3 < y1
  * 因此需要进行区间上的最大值查找 使用线段树记录每个x坐标对应的y坐标的最大值
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
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
        // down(x);
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
    vector<int> pos; // 用于对x坐标离散化
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        map<int, vector<int>> y_group, x_group;
        for(int i = 0; i < xCoord.size(); i++) {
            int x = xCoord[i], y = yCoord[i];
            y_group[y].push_back(x), x_group[x].push_back(y);
            pos.push_back(x);
        }
        scatter();
        SegmentTree st(pos.size());
        for(auto& [x, group] : x_group)
            sort(group.begin(), group.end());
        ll ans = 0;
        for(auto& [y, group] : y_group) {
            sort(group.begin(), group.end());
            for(int i = 0; i < group.size() - 1; i++) {
                int x1 = group[i], x2 = group[i + 1];
                int lo = find(x1), hi = find(x2);
                int y1 = find_pre(x_group[x1], y), y2 = find_pre(x_group[x2], y);
                if(y1 == y2 && y1 != -1 &&
                   (lo + 1 > hi - 1 || st.search(lo + 1, hi - 1) < y1)) {
                    ans = max(ans, (ll)(x2 - x1) * (ll)(y - y1));
                }
            }
            for(int x : group)
                st.add(find(x), y);
        }
        return ans == 0 ? -1 : ans;
    }

    int find_pre(vector<int>& arr, int val) {
        auto it = lower_bound(arr.begin(), arr.end(), val);
        if(it == arr.begin()) return -1;
        return arr[it - arr.begin() - 1];
    }

    void scatter() {
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
    }

    int find(int val) {
        return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
    }
};