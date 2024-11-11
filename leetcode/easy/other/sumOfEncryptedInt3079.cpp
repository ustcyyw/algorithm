/**
 * @Time : 2024/3/24-3:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sumOfEncryptedInt(vector<int>& nums) {
        int sum = 0;
        for(int num : nums) {
            string s = to_string(num);
            char maxV = *max_element(s.begin(), s.end());
            for(char& c : s)
                c = maxV;
            sum += stoi(s);
        }
        return sum;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}