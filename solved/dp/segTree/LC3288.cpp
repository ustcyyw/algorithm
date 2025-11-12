/**
 * @Time : 2025/1/8-12:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3288 动态规划 线段树优化
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e6 + 5;
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
            val[x] = max(val[x], v);
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
    int n, tx, ty, m;
    vector<int> pos;
    vector<vector<int>> points;
    int maxPathLength(vector<vector<int>>& points, int k) {
        this->n = points.size(), this->tx = points[k][0], this->ty = points[k][1];
        sort(points.begin(), points.end());
        this->points = points;
        for(auto& p : points)
            pos.push_back(p[1]);
        sort(pos.begin(), pos.end());
        pos.erase(unique(pos.begin(), pos.end()), pos.end());
        this->m = pos.size();
        int i = 0, j = 0, ans = stage1(i, j);
        SegmentTree st(m);
        vector<int> dp(n, 0);
        st.add(find(ty), ans);
        while(i < n) {
            int x = points[i][0];
            while(j < n && points[j][0] == x) {
                int y = points[j][1], hi = find(y);
                if(hi > 0) dp[j] = st.search(0, hi - 1) + 1;
                ans = max(dp[j], ans);
                j++;
            }
            j = i;
            while(j < n && points[j][0] == x) {
                if(dp[j] > 0) st.add(find(points[j][1]), dp[j]);
                j++;
            }
            i = j;
        }
        return ans;
    }

    int stage1(int& i, int& j) {
        SegmentTree st(m);
        vector<int> dp(n, 0);
        int flag = 0, ans = 0;
        while(i < n) {
            int x = points[i][0];
            while(j < n && points[j][0] == x) {
                int y = points[j][1], hi = find(y);
                int temp = hi == 0 ? 0 : st.search(0, hi - 1);
                dp[j] = max(temp + 1, 1);
                if(tx == x && ty == y) {
                    ans = dp[j], flag = 1;
                    break;
                }
                j++;
            }
            j = i;
            while(j < n && points[j][0] == x) {
                st.add(find(points[j][1]), dp[j]);
                j++;
            }
            i = j;
            if(flag) return ans;
        }
        return -1;
    }

    int find(int val) {
        return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
    }
};