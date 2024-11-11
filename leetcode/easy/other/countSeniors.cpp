/**
 * @Time : 2023/5/14-10:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSeniors(vector<string>& details) {
        int cnt = 0;
        for(string& info : details) {
            if(stoi(info.substr(11, 2)) > 60)
                cnt++;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}