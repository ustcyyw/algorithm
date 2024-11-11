/**
 * @Time : 2023/3/21-10:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size(), mod = 1e9 + 7;
        vector<int> aux(n + 1, 0), count(0, 0);
        for(auto& req : requests)
            aux[req[0]]++, aux[req[1] + 1]--;
        for(int i = 0, sum = 0; i < n; i++){
            sum += aux[i];
            count.push_back(sum);
        }
        sort(nums.begin(), nums.end()), sort(count.begin(), count.end());
        long res = 0;
        for(int i = 0; i < n; i++)
            res = (res + (long)nums[i] * count[i]) % mod;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}