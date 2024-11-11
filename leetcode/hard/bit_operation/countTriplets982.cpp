/**
 * @Time : 2022/12/14-4:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTriplets(vector<int>& nums) {
        unordered_map<int, int> map;
        for(int a : nums){
            for(int b : nums){
                int t = a & b;
                map[t] = map.count(t) ? map[t] + 1 : 1;
            }
        }
        int res = 0, full = (1 << 17) - 1;
        for(int num : nums){
            int u = full ^ num;
            for(int s = u; s; s = (s - 1) & u)
                res += map.count(s) ? map[s] : 0;
        }
        if(map.count(0)) res += map[0] * nums.size();
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}