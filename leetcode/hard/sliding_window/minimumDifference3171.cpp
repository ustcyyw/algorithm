/**
 * @Time : 2024/6/3-11:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size(), ans = INT_MAX;
        vector<int> cnt(32, 0);
        for(int lo = 0, hi = 0; hi < n; hi++) {
            int num = nums[hi];
            for(int i = 0; i < 32; i++)
                if((1 << i) & num) cnt[i]++;
            ans = min(ans, abs(k - get_val(cnt, lo, hi)));
            while(lo <= hi && get_val(cnt, lo, hi) < k) {
                for(int i = 0; i < 32; i++)
                    if((1 << i) & nums[lo]) cnt[i]--;
                lo++;
                ans = min(ans, abs(k - get_val(cnt, lo, hi)));
            }
        }
        return ans;
    }

    int get_val(vector<int>& cnt, int lo, int hi) {
        int val = 0, t = hi - lo + 1;
        for(int i = 0; i < 32; i++) {
            if(cnt[i] == t)
                val |= (1 << i);
        }
        return val;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}