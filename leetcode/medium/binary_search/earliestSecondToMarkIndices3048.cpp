/**
 * @Time : 2024/2/28-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& index) {
        int n = nums.size(), m = index.size();
        if(n > m) return -1;
        function<bool(int)> check = [&](int time) -> bool {
            vector<int> marked(n + 1, 0), it = index;
            int cnt = 0;
            for(int i = time - 1; i >= 0; i--) {
                if(!marked[index[i]]) marked[index[i]] = 1, cnt++;
                else it[i] = -1;
            }
            if(cnt != n) return false;
            for(int i = 0, free = 0; i < time; i++) {
                if(it[i] == -1) free++;
                else if(free >= nums[it[i] - 1]) free -= nums[it[i] - 1];
                else return false;
            }
            return true;
        };
        int lo = n, hi = m + 1;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo == m + 1 ? -1 : lo;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}