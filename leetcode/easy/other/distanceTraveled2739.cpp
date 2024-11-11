/**
 * @Time : 2023/7/19-5:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int distanceTraveled(int mainTank, int additionalTank) {
        int res = 0;
        while (mainTank >= 5 && additionalTank > 0) {
            int t1 = mainTank % 5;
            res += mainTank - t1;
            int t2 = min(mainTank / 5, additionalTank);
            additionalTank -= t2;
            mainTank = t1 + t2;
        }
        res += mainTank;
        return res * 10;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}