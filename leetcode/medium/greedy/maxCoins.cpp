/**
 * @Time : 2022/10/11-11:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(), piles.end());
        int res = 0;
        for(int i = piles.size() / 3; i < piles.size(); i += 2)
            res += piles[i];
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}