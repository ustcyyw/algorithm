/**
 * @Time : 2023/4/10-11:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> map;
        for(int i = 0; i < nums.size(); i++){
            int num = nums[i];
            if(!map.count(num)) map[num] = {};
            map[num].push_back(i);
        }
        vector<long long> res(nums.size(), 0);
        for(auto& p : map)
            group_distance(res, p.second);
        return res;
    }

    void group_distance(vector<long long>& res, vector<int>& index){
        int n = index.size();
        vector<long long> sum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            sum[i] = sum[i - 1] + index[i - 1];
        for(int i = 1; i <= n; i++)
            res[index[i - 1]] = (long long)index[i - 1] * (i - 1) - sum[i - 1]
                                + sum[n] - sum[i - 1] - (long long)index[i - 1] * (n - i + 1);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}