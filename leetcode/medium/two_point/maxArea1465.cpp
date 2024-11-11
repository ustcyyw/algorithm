/**
 * @Time : 2023/4/15-4:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mod = 1e9 + 7;
    int maxArea(int n, int m, vector<int>& h, vector<int>& v) {
        return max_len(n, h) * max_len(m, v) % mod;
    }

    long long max_len(int l, vector<int>& arr){
        sort(arr.begin(), arr.end());
        int n = arr.size(), res = max(arr[0], l - arr[n - 1]);
        for(int i = 0; i < n - 1; i++)
            res = max(res, arr[i + 1] - arr[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}