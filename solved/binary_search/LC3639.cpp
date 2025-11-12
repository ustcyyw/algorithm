/**
 * @Time : 2025/11/11-10:20
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3639 1853 二分答案
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTime(string s, vector<int>& order, int k) {
        int n = order.size(), lo = 0, hi = n;
        if((long long)n * (n + 1) / 2 < k) return -1;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(order, k, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(vector<int>& order, int k, int mid) {
        vector<int> arr;
        for(int i = 0; i <= mid; i++)
            arr.push_back(order[i]);
        sort(arr.begin(), arr.end());
        for(int i = 0, j = 0, cnt = 0, n = order.size(); i < n; i++) {
            if(arr[j] < i) j++;
            if(j == arr.size()) break;
            cnt += n - arr[j];
            if(cnt >= k) return true;
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}