/**
 * @Time : 2022/4/28-8:57 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long lo = time[0], hi = time[0];
        for(int& t : time)
            lo = min((long long)t, lo), hi = max((long long)t, hi);
        hi *= totalTrips;
        while (lo < hi){
            long long mid = (lo + hi) / 2;
            if(check(time, totalTrips, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(vector<int>& time, int totalTrips, int res){
        long long count = 0;
        for(int& t : time){
            count += res / t;
            if(count >= totalTrips) return true;
        }
        return false;
    }
};

int main(){

}