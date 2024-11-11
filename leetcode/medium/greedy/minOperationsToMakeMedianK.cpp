/**
 * @Time : 2024/4/7-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛392 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 排序nums后 要将其它数改变后在中位数的位置，原本那个位置的数也要改变 那不如直接改原本那个位置的数
     * 看将原本中位数变为k 其它数应该如何相应地变化
     */
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), mid = n / 2;
        if(nums[mid] == k) return 0;
        long long ans = 0;
        if(nums[mid] < k) {
            for(int i = mid; i < n && nums[i] < k; i++)
                ans += k - nums[i];
        } else {
            for(int i = mid; i >= 0 && nums[i] > k; i--)
                ans += nums[i] - k;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}