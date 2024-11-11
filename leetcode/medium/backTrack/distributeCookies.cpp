/**
 * @Time : 2022/6/30-1:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int res = 800002;
    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> arr = vector(k, 0);
        backTrack(cookies, arr, 0, k);
        return res;
    }

    void backTrack(vector<int>& cookies, vector<int>& arr, int cur, int k){
        if(cur == cookies.size()) {
            res = min(res, unfairPoint(arr));
            return;
        }
        int v = cookies[cur];
        for(int i = 0; i < k; i++){
            if(arr[i] + v >= res) continue;
            arr[i] += v;
            backTrack(cookies, arr, cur + 1, k);
            arr[i] -= v;
        }
    }

    int unfairPoint(vector<int>& arr){
        int temp = 0;
        for(int num : arr)
            temp = max(temp, num);
        return temp;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}