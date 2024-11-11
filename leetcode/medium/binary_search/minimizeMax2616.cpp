/**
 * @Time : 2023/4/11-2:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int lo = 0, hi = 1e9;
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(check(nums, p, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(vector<int>& nums, int p, int val){
        for(int i = 0; i < nums.size() - 1 && p; i++){
            if(nums[i + 1] - nums[i] <= val)
                p--, i++;
        }
        return p == 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}