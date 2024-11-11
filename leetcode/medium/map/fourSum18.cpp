/**
 * @Time : 2023/3/22-10:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<unordered_set<long>> sets(n);
        sets[n - 1].insert(nums[n - 1]);
        for(int i = n - 2; i >= 0; i--){
            sets[i] = sets[i + 1];
            sets[i].insert(nums[i]);
        }
        vector<vector<int>> res;
        for(int i = 0; i < n - 3; i++){
            if(i > 0 && nums[i - 1] == nums[i]) continue;
            for(int j = i + 1; j < n - 2; j++){
                if(j != i + 1 && nums[j - 1] == nums[j]) continue;
                for(int k = j + 1; k < n - 1; k++){
                    if(k != j + 1 && nums[k - 1] == nums[k]) continue;
                    long sum = (long)nums[i] + nums[j] + nums[k];
                    if(sets[k + 1].count(target - sum))
                        res.push_back({nums[i], nums[j], nums[k], (int)(target - sum)});
                }
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}