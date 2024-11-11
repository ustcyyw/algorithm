/**
 * @Time : 2023/12/17-2:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛376 t4
 */

/*
 * 转化为求最小距离的中位数贪心
 *
 * 1. 假定频数固定为cnt 要能取到相同的cnt个数 应该在最接近的cnt个数中做变换 因此要首先对数组进行排序
 * 2. 如果给定相邻的cnt个数，要将他们转化为某个相同的数val 并且操作次数最少
 *    本题的操作是任意一个数+1 或者 -1。因此实际上就是求这cnt个数到val的距离差之和
 *    中位数贪心 因此还要求出前缀和 根据中位数分左边和右边两部分的计算
 * 3. 频数固定的时候计算是否可以达到 具有单调性 使用二分
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    long long k;
    int maxFrequencyScore(vector<int>& nums, long long k) {
        sort(nums.begin(), nums.end());
        this->n = nums.size(), this->k = k;
        vector<long long> sum(n + 1, 0ll);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + nums[i - 1];
        int lo = 1, hi = n;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if(check(nums, sum, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<int>& nums, vector<long long>& sum, int len) {
        for(int lo = 0, hi = len - 1; hi < n; lo++, hi++) {
            long long mid = (lo + hi) >> 1, num = nums[mid];
            long long target = num * (mid - lo + 1) - (sum[mid + 1] - sum[lo])
                               + sum[hi + 1] - sum[mid + 1] - num * (hi - mid);
            if(target <= k) return true;
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}