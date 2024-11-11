/**
 * @Time : 2023/5/5-9:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int lo = 1, hi = 1e7 + 1;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(dist, hour, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo == 1e7 + 1 ? -1 : lo;
    }

    bool check(vector<int>& dist, double hour, int speed) {
        int time = 0, n = dist.size();
        for(int i = 0; i < n - 1; i++)
            time += dist[i] % speed == 0 ? dist[i] / speed : dist[i] / speed + 1;
        return time + 1.0 * dist[n - 1] / speed <= hour;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}