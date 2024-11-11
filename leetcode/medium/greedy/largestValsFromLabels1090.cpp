/**
 * @Time : 2022/11/2-8:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = values.size();
        vector<vector<int>> infos;
        for(int i = 0; i < n; i++)
            infos.push_back({values[i], labels[i]});
        sort(infos.begin(), infos.end(),
             [](vector<int>& a, vector<int>& b) -> bool {return a[0] < b[0];});
        vector<int> cnt(2e4 + 1, 0);
        int res = 0;
        for(int i = n - 1; i >= 0 && numWanted > 0; i--){
            vector<int>& cur = infos[i];
            if(cnt[cur[1]] >= useLimit) continue;
            cnt[cur[1]]++;
            res += cur[0];
            numWanted--;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}