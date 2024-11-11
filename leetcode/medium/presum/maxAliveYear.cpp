/**
 * @Time : 2022/6/21-10:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 差分
    int maxAliveYear(vector<int>& birth, vector<int>& death) {
        vector<int> year = vector(2002, 0);
        for(int i = 0; i < birth.size(); i++){
            year[birth[i]]++;
            year[death[i] + 1]--;
        }
        int res = 0;
        for(int i = 1900; i <= 2000; i++){
            year[i] += year[i - 1];
            if(year[i] > year[res]) res = i;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}