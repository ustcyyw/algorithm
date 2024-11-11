/**
 * @Time : 2023/2/11-1:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size(), res = 0;
        for(int i = 1; i < n - 1; i++){
            if(arr[i - 1] < arr[i] && arr[i] > arr[i + 1]){
                int lo = i - 1, hi = i + 1;
                while (lo >= 0 && arr[lo] < arr[lo + 1]) lo--;
                while (hi < n && arr[hi] < arr[hi - 1]) hi++;
                res = max(res, hi - lo - 1);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}