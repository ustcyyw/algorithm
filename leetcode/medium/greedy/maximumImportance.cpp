/**
 * @Time : 2022/7/15-9:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<int> degree = vector(n, 0);
        for(auto road : roads)
            degree[road[0]]++, degree[road[1]]++;
        sort(degree.begin(), degree.end());
        long long res = 0;
        for(int i = degree.size() - 1; i >= 0; i--)
            res += (i + 1) * (long)degree[i];
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}