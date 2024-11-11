/**
 * @Time : 2023/2/11-8:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        long sum = 0, mod = 1e9 + 7, res = 0;
        vector<long> arr;
        for(int i = 0; i < n; i++){
            sum = 0;
            for(int j = i; j < n; j++){
                sum = (sum + nums[j]) % mod;
                arr.push_back(sum);
            }
        }
        sort(arr.begin(), arr.end());
        for(int i = left - 1; i < right; i++)
            res = (res + arr[i]) % mod;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}