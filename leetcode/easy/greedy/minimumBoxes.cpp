/**
 * @Time : 2024/3/10-2:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛388 t1
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        sort(capacity.begin(), capacity.end());
        int sum = accumulate(apple.begin(), apple.end(), 0), n = capacity.size();
        for(int i = n - 1; i >= 0; i--) {
            sum -= capacity[i];
            if(sum <= 0) return n - i;
        }
        return -1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}