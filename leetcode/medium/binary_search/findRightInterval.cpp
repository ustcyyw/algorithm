/**
 * @Time : 2022/5/26-1:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<vector<int>> infos;
        int n = intervals.size();
        for(int i = 0; i < n; i++)
            infos.push_back({intervals[i][0], intervals[i][1], i});
        sort(infos.begin(), infos.end(),
             [](vector<int> a, vector<int>b) -> bool {return a[0] < b[0];});
        vector<int> res = vector(n, 0);
        for(int i = 0; i < n; i++){
            vector<int> info = infos[i];
            res[info[2]] = search(infos, info[1], i, n);
        }
        return res;
    }
    // 大于等于end的最小的start对应的下标
    int search(vector<vector<int>>& infos, int end, int lo, int n){
        int hi = n;
        while (lo < hi){
            int mid = (lo + hi) / 2;
            if(infos[mid][0] < end) lo = mid + 1;
            else hi = mid;
        }
        return lo == n ? -1 : infos[lo][2];
    }
};

int main(){

}