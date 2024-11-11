/**
 * @Time : 2024/1/29-12:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long flowerGame(int n, int m) {
        long long cnt = 0;
        for(int x = 1; x <= n; x++) {
            if(x % 2 == 1) cnt += m / 2;
            else cnt += (m + 1) / 2;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}