/**
 * @Time : 2022/9/18-3:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());
        int res = 0, n = players.size(), m = trainers.size();
        for(int i = 0, j = 0; i < n && j < m; i++, j++){
            while (j < m && players[i] > trainers[j]) j++;
            if(j < m) res++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}