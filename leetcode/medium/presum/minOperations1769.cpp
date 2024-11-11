/**
 * @Time : 2022/12/9-12:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        vector<int> res(n, 0);
        for(int i = 0, sum = 0; i < n; i++){
            res[i] = sum;
            sum += sum + boxes[i] - '0';
        }
        for(int i = n - 1, sum = 0; i >= 0; i--){
            res[i] += sum;
            sum += sum + boxes[i] - '0';
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}