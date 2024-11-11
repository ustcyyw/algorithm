/**
 * @Time : 2023/12/10-3:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛119 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size(), len = 1;
        unordered_map<int, int> cnt;
        for(int lo = 0, hi = 0; hi < n; hi++) {
            int num = nums[hi];
            cnt[num]++;
            while(cnt[num] > k) {
                cnt[nums[lo]]--;
                lo++;
            }
            len = max(len, hi - lo + 1);
        }
        return len;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}