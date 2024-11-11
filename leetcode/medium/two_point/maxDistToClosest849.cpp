/**
 * @Time : 2023/3/4-3:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        seats.push_back(1);
        int n = seats.size(), res = 0;
        for(int i = -1, j = 0; j < n; j++){
            while (j < n && seats[j] == 0) j++;
            if(i == -1 || j == n) res = max(res, j - i - 1);
            else res = max(res, (j - i) / 2);
            i = j;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}