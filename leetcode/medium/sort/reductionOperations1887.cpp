/**
 * @Time : 2022/11/11-5:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        unordered_map<int, int> map;
        for(int num : nums){
            if(map.count(num)) map[num]++;
            else map[num] = 1;
        }
        vector<pair<int, int>> arr;
        for(auto& pair : map)
            arr.push_back(pair);
        sort(arr.begin(), arr.end());
        int res = 0, n = arr.size();
        for(int i = n - 1; i > 0; i--){
            res += arr[i].second;
            arr[i - 1].second += arr[i].second;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}