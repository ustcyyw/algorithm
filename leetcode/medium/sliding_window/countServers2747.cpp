/**
 * @Time : 2023/7/20-5:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        vector<int> arr;
        for(vector<int>& log : logs) arr.push_back(log[1]);
        for(int q : queries) arr.push_back(q);
        unordered_map<int, int> map = scatter(arr);
        int N = arr.size();

        vector<vector<int>> ids(N);
        vector<int> aux(N, 0), res;
        for(vector<int>& log : logs)
            ids[map[log[1]]].push_back(log[0]);
        unordered_map<int, int> cnt;
        for(int hi = 0, lo = 0; hi < N; hi++) {
            for(int id : ids[hi])
                cnt[id] = cnt.count(id) ? cnt[id] + 1 : 1;
            while (arr[hi] - arr[lo] > x) {
                for(int id : ids[lo]) {
                    cnt[id]--;
                    if(cnt[id] == 0) cnt.erase(cnt.find(id));
                }
                lo++;
            }
            aux[hi] = (int)cnt.size();
        }
        for(int q : queries)
            res.push_back(n - aux[map[q]]);
        return res;
    }

    unordered_map<int, int> scatter(vector<int>& arr) {
        unordered_map<int, int> map;
        sort(arr.begin(), arr.end());
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        for(int i = 0; i < arr.size(); i++)
            map[arr[i]] = i;
        return map;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}