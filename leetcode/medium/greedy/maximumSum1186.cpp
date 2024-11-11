/**
 * @Time : 2023/2/20-10:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size(), res = -1e9;
        vector<int> left(n + 1, 0);
        for(int i = 0, sum = 0, val = 0; i < n; i++){
            sum += arr[i];
            left[i + 1] = sum - val;
            val = min(val, sum);
        }
        for(int i = n - 1, sum = 0, val = 0; i >= 0; i--){
            int t1 = max(left[i], 0), t2 = max(sum - val, 0);
            if(arr[i] >= 0) res = max(res, arr[i] + t1 + t2);
            else { // arr[i] < 0的情况，需要考虑取舍哪一部分 保证非空
                if((i != 0 && left[i] >= 0) || (i != n - 1 && sum - val >= 0)) // 左边或右边可以取一边的情况
                    res = max(res, t1 + t2);
                else res = max(res, arr[i]);
            }
            sum += arr[i];
            val = min(val, sum);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}