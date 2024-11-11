/**
 * @Time : 2022/6/11-8:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：20 ms, 在所有 C++ 提交中击败了83.71%的用户
     * 内存消耗：22 MB, 在所有 C++ 提交中击败了6.79%的用户
     */
    bool validMountainArray(vector<int>& arr) {
        int flag = 1, n = arr.size();
        if(n < 3) return false;
        if(arr[0] >= arr[1] || arr[n - 2] <= arr[n - 1]) return false;
        for(int i = 1; i < n; i++){
            if(arr[i] == arr[i - 1]) return false;
            if(arr[i - 1] * flag > arr[i] *  flag){
                if(flag == -1) return false;
                else flag = -1;
            }
        }
        return true;
    }
};

int main(){

}