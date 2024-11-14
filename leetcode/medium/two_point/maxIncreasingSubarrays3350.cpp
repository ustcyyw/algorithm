/**
 * @Time : 2024/11/13-9:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        vector<int> arr;
        int n = nums.size();
        for(int i = 0, j; i < n; ) {
            j = i + 1;
            while(j < n && nums[j] > nums[j - 1]) j++;
            arr.push_back(j - i);
            i = j;
        }
        int ans = 0;
        for(int i = 0, m = arr.size(); i < m; i++) {
            if(i != m - 1) ans = max(ans, min(arr[i], arr[i + 1]));
            ans = max(ans, arr[i] / 2);
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}