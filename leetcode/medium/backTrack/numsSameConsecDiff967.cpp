/**
 * @Time : 2023/3/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, k;
    vector<int> res;
    vector<int> numsSameConsecDiff(int n, int k) {
        this->n = n, this->k = k;
        for(int i = 1; i <= 9; i++)
            back_track(i, i, 1);
        return res;
    }

    void back_track(int num, int pre, int cur){
        if(cur == n) {
            res.push_back(num);
            return;
        }
        if(pre + k <= 9)
            back_track(num * 10 + pre + k, pre + k, cur + 1);
        if(k != 0 && (pre - k > 0 || (pre - k == 0 && cur != 0)))
            back_track(num * 10 + pre - k, pre - k, cur + 1);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}