/**
 * @Time : 2022/11/26-8:53 AM
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
    vector<vector<int>> cache;
    int stoneGameII(vector<int>& piles) {
        n = piles.size();
        cache = vector(n, vector(n + 1, INT_MIN));
        int total = accumulate(piles.begin(), piles.end(), 0);
        int diff = maxDiff(piles, 0, 1); // alice 比bob多的
        return (diff + total) / 2;
    }

    int maxDiff(vector<int>& piles, int lo, int M){
        if(lo == n) return 0;
        if(cache[lo][M] != INT_MIN) return cache[lo][M];
        int res = INT_MIN;
        for(int i = lo, sum = 0; i - lo + 1 <= 2 * M && i < n; i++){
            sum += piles[i];
            int t = max(M, i - lo + 1), diff = maxDiff(piles, i + 1, min(t, n));
            res = max(res, sum - diff);
        }
        cache[lo][M] = res;
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {2,7,9,4,4};
    s.stoneGameII(arr);
    cout << 0 << endl;
}