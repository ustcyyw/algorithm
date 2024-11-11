/**
 * @Time : 2023/4/24-11:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(int n) {
        int cnt = 0;
        bitset<20> num(n);
        for (int i = 0, j = 0; i < 20; i = j) {
            while (i < 20 && num[i] == 0) i++;
            if(i == 20) break;
            j = i + 1;
            while (j < 20 && num[j]) j++;
            if (j - i > 1) num[j] = 1;
            cnt++;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}