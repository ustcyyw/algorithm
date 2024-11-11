/**
 * @Time : 2022/11/15-5:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int sumA = 0, sumB = 0, n = aliceValues.size();
        vector<vector<int>> arr;
        for(int i = 0; i < n; i++)
            arr.push_back({aliceValues[i] + bobValues[i], i});
        sort(arr.begin(), arr.end());
        for(int i = n - 1, flag = 0; i >= 0; i--, flag++){
            if(flag % 2 == 0) sumA += aliceValues[arr[i][0]];
            else sumB += bobValues[arr[i][0]];
        }
        if(sumA == sumB) return 0;
        return sumA > sumB ? 1 : -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}