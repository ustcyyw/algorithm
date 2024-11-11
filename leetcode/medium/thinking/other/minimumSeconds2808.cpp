/**
 * @Time : 2023/8/9-4:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        unordered_map<int, vector<int>> map;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            int num = nums[i];
            if(!map.count(num)) map[num] = {};
            map[num].push_back(i);
        }
        function<int(vector<int>&)> max_interval = [&](vector<int>& arr) -> int {
            if(arr.size() == 1) return n;
            int res = arr[0] + n - arr.back();
            for(int i = 0; i < arr.size() - 1; i++)
                res = max(res, arr[i + 1] - arr[i]);
            return res;
        };
        int res = INT_MAX;
        for(auto& pair : map)
            res = min(res, max_interval(pair.second) / 2);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}