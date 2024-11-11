/**
 * @Time : 2023/9/5-9:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

vector<string> tail = {"00","25","50","75"};
class Solution {
public:
    int minimumOperations(string num) {
        int res = num.size();
        for(char c : num) {
            if(c == '0')
                res = num.size() - 1;
        }
        for(int i = 0; i < 4; i++)
            res = min(res, count(num, tail[i]));
        return res;
    }

    int count(string& num, string& t) {
        int res = 0, j = 1;
        for(int i = num.size() - 1; i >= 0 && j >= 0; i--) {
            if(num[i] != t[j]) res++;
            else j--;
        }
        return j == -1 ? res : INT_MAX;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}