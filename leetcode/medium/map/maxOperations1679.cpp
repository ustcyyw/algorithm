/**
 * @Time : 2023/2/11-8:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        int res = 0;
        unordered_map<int, int> map;
        for(int num : nums){
            if(map.count(k - num) && map[k - num] > 0){
                map[k - num]--;
                res++;
            } else map[num] = map.count(num) ? map[num] + 1 : 1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}