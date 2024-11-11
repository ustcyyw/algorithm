/**
 * @Time : 2023/10/15-12:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛367 t4
 */
#include<bits/stdc++.h>
using namespace std;

const int mod = 12345;
class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        vector<int> nums;
        for(auto& line : grid) {
            for(int num : line)
                nums.push_back(num);
        }
        int n = nums.size(), col = grid[0].size();
        vector<long> suf(n, 0);
        suf[n - 1] = nums[n - 1];
        for(int i = n - 2; i >= 0; i--)
            suf[i] = suf[i + 1] * nums[i] % mod;
        long t = 1;
        for(int i = 0; i < n; i++) {
            if(i != n - 1) {
                grid[i / col][i % col] = t * suf[i + 1] % mod;
                t = t * nums[i] % mod;
            }
            else grid[i / col][i % col] = t;
        }
        return grid;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}