/**
 * @Time : 2022/10/31-1:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        vector<int> degree(1e5 + 1, -1);
        for(auto& match : matches){
            int w = match[0], l = match[1];
            if(degree[w] == -1) degree[w] = 0;
            if(degree[l] == -1) degree[l] = 0;
            degree[l]++;
        }
        vector<int> winners, losers;
        for(int i = 1; i < degree.size(); i++){
            if(degree[i] == -1) continue;
            if(degree[i] == 0) winners.push_back(i);
            if(degree[i] == 1) losers.push_back(i);
        }
        return {winners, losers};
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}