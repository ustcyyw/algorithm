/**
 * @Time : 2023/2/24-10:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kthGrammar(int n, int k) {
        if(n == 1) return 0;
        int t = kthGrammar(n - 1, (k + 1) / 2);
        // if(t == 0) return k % 2 == 0 ? 1 : 0;
        // else return k % 2 == 0 ? 0 : 1;
        return (k % 2 + t + 1) % 2;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}