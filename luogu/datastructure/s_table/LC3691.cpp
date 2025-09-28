/**
 * @Time : 2025/9/28-10:11
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3691 st表 二分
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

class STable {
    int n, m;
    vector<vector<int>> dp;

    int f(int num1, int num2) {
        // 可以替换为其它函数
        return max(num1, num2);
    }

public:
    STable(vector<int>& nums) {
        n = nums.size(), m = log2(n);
        dp.assign(n, vector(m + 1, 0));
        for(int i = 0; i < n; i++)
            dp[i][0] = nums[i];
        for(int j = 1; j <= m; j++) {
            int pj = 1 << (j - 1);
            for(int i = 0; i + pj < n; i++) {
                dp[i][j] = f(dp[i][j - 1], dp[i + pj][j - 1]);
            }
        }
    }

    int search(int l, int r) {
        int len = r - l + 1, j = log2(len);
        return f(dp[l][j], dp[r - (1 << j) + 1][j]);
    }
};

class Solution {
public:
    int n;
    long long maxTotalValue(vector<int>& nums, int k) {
        n = nums.size();
        vector<int> nums2;
        for(int i = 0; i < n; i++)
            nums2.push_back(-nums[i]);
        STable st1(nums), st2(nums2);
        ll ans = 0, val = find(st1, st2, k);
        for(int i = 0; i < n && k; i++) {
            for(int j = n - 1; j >= i && k; j--) {
                int maxV = st1.search(i, j), minV = st2.search(i, j);
                if(maxV + minV > val) k--, ans += maxV + minV;
                else break;
            }
        }
        ans += val * k;
        return ans;
    }

    int find(STable& st1, STable& st2, int k) {
        int lo = 0, hi = 1e9;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if(check(st1, st2, mid, k)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(STable& st1, STable& st2, int val, int k) {
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            int lo = i, hi = n - 1;
            if(st1.search(i, hi) + st2.search(i, hi) < val) continue;
            while(lo < hi) {
                int mid = (lo + hi) >> 1;
                if(st1.search(i, mid) + st2.search(i, mid) >= val) hi = mid;
                else lo = mid + 1;
            }
            cnt += n - 1 - lo + 1;
            if(cnt >= k) return true;
        }
        return false;
    }
};