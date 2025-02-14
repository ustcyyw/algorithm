/**
 * @Time : 2025/2/13-7:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3449 二分答案 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 3e4 + 5, P = 13331;

class Solution {
public:
    /*
     * 两个维度的坐标 取差值最小的代表距离
     * 如果答案是x，那么该点对两个维度的坐标都 >= x
     */
    int n;
    long long maxScore(vector<int>& points, int m) {
        this->n = points.size();
        points.push_back(0);
        ll lo = 0, hi = 1e15;
        while(lo < hi) {
            ll mid = (lo + hi + 1) >> 1;
            if(check(points, m, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<int>& points, ll m, ll val) {
        for(ll i = 0, cur = 0; i < n; i++) {
            if(m < 0) return false;
            if(cur >= val) {
                if(i != n - 1) m--; // 如果不是最后一个元素 还需要一次操作移动下标i向右
                cur = 0;
                continue;
            }
            ll need = val - cur, p = points[i];
            ll cnt = need % p == 0 ? need / p : need / p + 1;
            m -= cnt * 2 - 1; // 在当前数和下一个数之间反复横跳
            cur = (cnt - 1) * points[i + 1];
        }
        return m >= 0;
    }
};