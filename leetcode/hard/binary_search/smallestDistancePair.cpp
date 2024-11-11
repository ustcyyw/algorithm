/**
 * @Time : 2022/6/17-11:25 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int lo = 0, hi = nums[nums.size() - 1] - nums[0];
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1, count = lessThan(nums, mid);
            if(count < k) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    int lessThan(vector<int>& nums, int key){
        int count = 0, lo = 0, hi = 0, n = nums.size();
        while (lo < n){
            while (hi < n && nums[hi] - nums[lo] < key) hi++;
            count += hi - lo - 1;
            lo++;
        }
        return count;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,3,1};
    cout <<  s.smallestDistancePair(arr, 1) << endl;
}