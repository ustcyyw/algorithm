/**
 * @Time : 2022/12/26-9:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());
        int n = price.size(), lo = 0, hi = price[n - 1] - price[0];
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1;
            if(check(price, k, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<int>& price, int k, int val){
        int cnt = 1, n = price.size();
        for(int i = 0, j = 0; i < n; ){
            while (j < n && price[j] - price[i] < val) j++;
            if(j < n) cnt++;
            i = j;
        }
        return cnt >= k;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}