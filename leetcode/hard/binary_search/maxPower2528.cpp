/**
 * @Time : 2023/1/9-4:23 PM
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
    long long maxPower(vector<int>& stations, int r, int k) {
        n = stations.size();
        vector<long long> info(n + 1, 0);
        for(int i = 0; i < n; i++){
            int lo = max(0, i - r), hi = min(n - 1, i + r);
            info[lo] += stations[i], info[hi + 1] -= stations[i];
        }
        long long lo = 0, hi = 1e11;
        while (lo < hi){
            long long mid = (hi - lo + 1) / 2 + lo;
            if(check(info, mid, k, r)) lo = mid;
            else hi = mid - 1;
        }
        return (long long)lo;
    }
    // 差分的思想
    bool check(vector<long long> info, long long val, int k, int r){
        long long sum = 0;
        for(int i = 0; i < n; i++){
            sum += info[i];
            if(sum >= val) continue;
            // 当前城市不够val的情况下
            long long diff = val - sum;
            if(k - diff < 0) return false;
            k -= diff;
            if(r != 0){
                sum += diff;
                int lo = min(n - 1, i + r); // 贪心地要将补建的电站建在能覆盖当前位置的最远处，也就是i + r
                info[min(n - 1, lo + r) + 1] -= diff;
            }
        }
        return true;
    }
};

int main(){
    Solution s;
    vector<int> arr = {13,12,8,14,7};
//    s.maxPower(arr, 1, 2);
    cout << s.maxPower(arr, 2, 23) << endl;
}