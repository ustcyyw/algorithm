/**
 * @Time : 2022/6/23-11:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> pairSums(vector<int>& nums, int target) {
        vector<vector<int>> res;
        unordered_map<int, int> map;
        for(int num : nums){
            int other = target - num;
            if(map.find(other) != map.end() && map[other] > 0){
                res.push_back({other, num});
                map[other]--;
            }
            else map[num] = map.find(num) != map.end() ? map[num] + 1 : 1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}