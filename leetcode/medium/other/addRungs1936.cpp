/**
 * @Time : 2022/12/15-9:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int addRungs(vector<int>& rungs, int dist) {
        int res = rungs[0] % dist == 0 ? rungs[0] / dist - 1 : rungs[0] / dist;
        for(int i = 0; i < rungs.size() - 1; i++){
            int diff = rungs[i + 1] - rungs[i];
            res += dist % diff == 0 ? diff / dist - 1 : diff / dist;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}