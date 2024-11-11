/**
 * @Time : 2024/2/4-9:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛123 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long sum = 0, res = LONG_LONG_MIN;
        unordered_map<int, long long> map;
        for(int num : nums) {
            sum += num;
            if(map.count(num - k)) res = max(res, sum - map[num - k]);
            if(map.count(num + k)) res = max(res, sum - map[num + k]);
            if(map.count(num)) map[num] = min(map[num], sum - num);
            else map[num] = sum - num;
        }
        return res == LONG_LONG_MIN ? 0 : res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}