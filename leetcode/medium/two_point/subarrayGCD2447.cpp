/**
 * @Time : 2022/10/25-11:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarrayGCD(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> arr(n, vector(n, 0));
        for(int i = 0; i < n; i++){
            int temp = nums[i];
            for(int j = i; j < n; j++){
                temp = gcd(temp, nums[j]);
                arr[i][j] = temp;
            }
        }
        int res = 0;
        for(int i = 0; i < n; i++){
            int lo = i;
            while (lo < n && arr[i][lo] > k) lo++;
            int hi = lo;
            while (hi < n && arr[i][lo] == k) hi++;
            res += hi - lo;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}