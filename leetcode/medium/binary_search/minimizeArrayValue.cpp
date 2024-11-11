/**
 * @Time : 2022/10/16-3:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    int minimizeArrayValue(vector<int>& nums) {
        n = nums.size();
        int lo = INT_MAX, hi = 0;
        for(int num : nums)
            lo = min(lo, num), hi = max(hi, num);
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(check(nums, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(vector<int>& nums, int val){
        vector<long long> aux(n, 0ll);
        aux[n - 1] = nums[n - 1];
        for(int i = n - 1; i > 0; i--){
            long long diff = aux[i] - val;
            if(diff > 0) aux[i - 1] = nums[i - 1] + diff;
            else aux[i - 1] = nums[i - 1];
        }
        return aux[0] <= val;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}