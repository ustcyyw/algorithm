/**
 * @Time : 2024/4/28-10:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛395 t4 二分+滑动窗口
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int mp[N];

class Solution {
public:
    ll n, m;
    int medianOfUniquenessArray(vector<int> &nums) {
        n = nums.size(), m = (n * (n + 1) / 2 + 1) / 2;
        int lo = 1, hi = (int) n / 2;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (check(nums, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    // 检查<=num的数 是否超过m个
    // 枚举右端点 查看左端点 保证区间内元素个数 <= num
    bool check(vector<int>& nums, int num) {
        memset(mp, 0, sizeof(mp));
        ll cnt = 0, sz = 0;
        for(int i = 0, j = 0; i < n; i++) {
            if(++mp[nums[i]] == 1) sz++;
            while(sz > num) {
                if(--mp[nums[j]] == 0) sz--;
                j++;
            }
            cnt += i - j + 1;
            if(cnt >= m) return true;
        }
        return false;
    }
};