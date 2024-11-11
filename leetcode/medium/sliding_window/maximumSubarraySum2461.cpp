/**
 * @Time : 2023/5/5-10:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long res = 0, sum = 0;
        int n = nums.size(), left = 0, right = 0, cnt = 0;
        vector<int> map(1e5 + 1, 0);
        while (right < n) {
            int num = nums[right];
            sum += num;
            if(++map[num] == 1) cnt++;
            if(right - left + 1 > k) {
                int t = nums[left++];
                sum -= t;
                if(--map[t] == 0) cnt--;
            }
            if(right - left + 1 == k && cnt == k)
                res = max(res, sum);
            right++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}