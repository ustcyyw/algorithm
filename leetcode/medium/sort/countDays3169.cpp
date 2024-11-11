/**
 * @Time : 2024/6/3-11:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());
        int ans = 0, time = 1;
        for(auto & meeting : meetings) {
            int lo = meeting[0], hi = meeting[1];
            if(time < lo) ans += lo - time;
            time = max(time, hi + 1);
        }
        ans += days - time + 1;
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}