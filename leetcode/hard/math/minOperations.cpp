/**
 * @Time : 2022/7/19-2:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        int n = numsDivide.size(), num = numsDivide[0];
        for(int i = 1; i < n; i++)
            num = gcd(num, numsDivide[i]);
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); i++){
            if(num % nums[i] == 0)
                return i;
        }
        return -1;
    }

    int gcd(int a, int b){
        if(a < b) return gcd(b, a);
        if(b == 0) return a;
        return gcd(b, a % b);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}