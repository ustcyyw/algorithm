/**
 * @Time : 2022/4/27-12:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> cache;
    unordered_map<int, int> map; // val -> index
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        cache = vector(n, vector(n, 0));
        for(int i = 0; i < n; i++)
            map[arr[i]] = i;
        int res = 0;
        for(int j = 1; j < n; j++){
            for(int i = j - 1; i >= 0; i--)
                res = max(res, maxLen(arr, i, j));
        }
        return res < 3 ? 0 : res;
    }

    int maxLen(vector<int>& arr, int i, int j){
        if(i == 0) return 2;
        if(cache[i][j] != 0) return cache[i][j];
        int pre_num = arr[j] - arr[i];
        int k = pre_num < arr[i] && map.find(pre_num) != map.end() ? map[pre_num] : -1;
        cache[i][j] = k == -1 ? 2 : maxLen(arr, k, i) + 1;
        return cache[i][j];
    }
};

int main(){

}