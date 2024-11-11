/**
 * @Time : 2022/12/13-4:36 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        int res = -1;
        sort(nums.begin(), nums.end());
        unordered_map<int, int> map;
        for(int num : nums){
            int t = (int)sqrt(num);
            if(t * t == num && map.count(t)){
                map[num] = map[t] + 1;
                res = max(res, map[num]);
            } else map[num] = 1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}