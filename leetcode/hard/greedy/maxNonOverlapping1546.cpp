/**
 * @Time : 2022/12/26-9:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     *
     */
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size(), res = 0, index = -1;
        unordered_map<int, int> map;
        map[0] = -1;
        for(int i = 0, sum = 0; i < n; i++){
            sum += nums[i];
            int d = sum - target;
            if(map.count(d) && map[d] >= index){
                res++;
                index = i;
            }
            map[sum] = i;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}