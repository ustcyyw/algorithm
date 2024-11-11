/**
 * @Time : 2022/11/7-5:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    vector<int> cache, sum;
    int minSessions(vector<int>& tasks, int sessionTime) {
        n = tasks.size();
        int full = (1 << n) - 1;
        cache = vector(full + 1, -1), sum = vector(full + 1, 0);
        for(int s = full; s; s = (s - 1) & full){
            for(int j = 0; j < n; j++)
                if((1 << j) & s) sum[s] += tasks[j];
        }
        return min_count(tasks, full, sessionTime);
    }

    int min_count(vector<int>& tasks, int status, int time){
        if(status == 0) return 0;
        if(cache[status] != -1) return cache[status];
        int cnt = INT_MAX;
        for(int s = status; s; s = (s - 1) & status){
            if(sum[s] <= time)
                cnt = min(cnt, min_count(tasks, status ^ s, time));
        }
        cache[status] = cnt + 1;
        return cnt + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}