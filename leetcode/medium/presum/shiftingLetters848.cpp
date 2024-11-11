/**
 * @Time : 2023/3/4-3:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        int n = s.size();
        long sum = accumulate(shifts.begin(), shifts.end(), 0l);
        for(int i = 0; i < n; i++){
            int t = sum % 26;
            if(s[i] + t > 'z') s[i] = s[i] + t - 26;
            else s[i] = s[i] + t;
            sum -= shifts[i];
        }
        return s;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}