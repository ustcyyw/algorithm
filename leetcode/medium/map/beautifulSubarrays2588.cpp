/**
 * @Time : 2023/4/17-5:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        unordered_map<int, int> map;
        map[0] = 1;
        int s = 0;
        long long res = 0;
        for(int num : nums){
            for(int i = 0; i < 21; i++) {
                int t = 1 << i;
                if(num & t) s ^= t;
            }
            map[s] = map.count(s) ? map[s] + 1 : 1;
            res +=  map[s] - 1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}