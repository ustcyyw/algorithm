/**
 * @Time : 2023/1/9-9:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int xorBeauty(vector<int>& nums) {
        vector<int> counts(32, 0), bit(32, 0);
        for(int num : nums){
            for(int i = 1; i < 32; i++){
                if(((1 << i) & num) > 0)
                    counts[i]++;
            }
        }
        for(int num : nums){
            for(int i = 1; i < 32; i++){
                if(((1 << i) & num) > 0)
                    bit[i] = (bit[i] + (long)counts[i] * counts[i]) % 2;
            }
        }
        int ans = 0;
        for(int i = 1; i < 32; i++){
            if(bit[i]) ans ^= 1 << i;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}