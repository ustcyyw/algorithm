/**
 * @Time : 2024/5/27-4:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛131 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x) {
        unordered_map<int, int> map;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != x) continue;
            map[map.size() + 1] = i;
        }
        vector<int> res;
        for(int num : queries)
            res.push_back(map.count(num) ? map[num] : -1);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}