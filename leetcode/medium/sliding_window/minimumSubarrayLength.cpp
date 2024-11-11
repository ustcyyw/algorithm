/**
 * @Time : 2024/3/31-10:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛127 t3
 */
 /*
  * 子数组的或操作
  * 如果nums[l, r]上所有元素位或 >= k，那么[l, r]上的子数组可能也能位或 >= k
  * 如果nums[l, r]上所有元素位或 < k，那么[l, r]上的子数组一定位或 < k
  * 因此在枚举子数组左端口时 达不到位或 >= k，就需要扩展右边界
  * 如果[l,r]刚好 >= k， 考虑 l = l + 1，此时不用考虑 r = r - 1，因为[l, r - 1]时不满足条件
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size(), res = INT_MAX, cnt[33] = {0};
        function<void(int, int)> change = [&](int num, int sign) {
            for(int i = 0; i < 32; i++) {
                if((1 << i) & num)
                    cnt[i] += sign * 1;
            }
        };
        function<int()> cal = [&]() -> int {
            int s = 0;
            for(int i = 0; i < 32; i++)
                if(cnt[i]) s |= 1 << i;
            return s;
        };
        for(int lo = 0, hi = 0; hi < n; hi++) {
            change(nums[hi], 1);
            while(lo <= hi && cal() >= k) {
                res = min(res, hi - lo + 1);
                change(nums[lo++], -1);
            }
        }
        return res == INT_MAX ? -1: res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}