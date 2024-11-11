/**
 * @Time : 2024/5/27-2:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛399 t4
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 5e4 + 5, mod = 1e9 + 7;
#define ls x << 1
#define rs (x << 1) | 1

class Solution {
public:
    // 分别是[], [), (], ()区间上的最大子序列和
    vector<vector<ll>> sum;
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        sum.assign(4 * n + 4, vector(4, 0ll));
        for(int i = 0; i < n; i++)
            add(1, 0, n - 1, i, nums[i]);
        ll ans = 0;
        for(auto& query : queries) {
            add(1, 0, n - 1, query[0], query[1]);
            vector<ll> temp = search(1, 0, n - 1, 0, n - 1);
            ll mv = 0;
            for(ll v : temp)
                mv = max(mv, v);
            ans = (ans + mv) % mod;
        }
        return ans;
    }

    vector<ll> search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return sum[x];
        int mid = (l + r) >> 1;
        vector<ll> res(4, LONG_LONG_MIN);
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) {
            if(res[0] != LONG_LONG_MIN) {
                vector<ll> aux(4, 0ll), rt = search(rs, mid + 1, r, a, b);
                update(l, r, aux, res, rt);
                swap(res, aux);
            } else res = search(rs, mid + 1, r, a, b);
        }
        return res;
    }

    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            sum[x][0] = max(0, v);
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        update(l, r, sum[x], sum[ls], sum[rs]);
    }

    void update(int l, int r, vector<ll>& arr, vector<ll>& left, vector<ll>& right) {
        if(l + 1 == r) {
            arr[0] = 0, arr[3] = 0;
            arr[1] = left[0], arr[2] = right[0];
        } else {
            arr[0] = max({left[1] + right[2], left[0] + right[2], left[1] + right[0]});
            arr[1] = max({left[0] + right[3], left[1] + right[1], left[1] + right[3]});
            arr[2] = max({left[3] + right[0], left[3] + right[2], left[2] + right[2]});
            arr[3] = max({left[2] + right[3], left[3] + right[1], left[3] + right[3]});
        }
    }
};