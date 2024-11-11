/**
 * @Time : 2023/4/20-4:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> id;
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        for(int i = 0; i < n; i++)
            id.push_back(i);
        for(auto& pair : pairs)
            connect(pair[0], pair[1]);
        unordered_map<int, vector<int>> map;
        unordered_map<int, int> point;
        for(int i = 0; i < n; i++){
            int p = find(i);
            if(!map.count(p)) map[p] = vector(26, 0);
            if(!point.count(p)) point[p] = 0;
            map[p][s[i] - 'a']++;
        }
        for(int i = 0; i < n; i++){
            int p = find(i);
            vector<int>& count = map[p];
            while (count[point[p]] == 0) point[p]++;
            s[i] = (char)(point[p] + 'a');
            count[point[p]]--;
        }
        return s;
    }

    int find(int p){
        if(id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }

    void connect(int p, int q){
        p = find(p), q = find(q);
        id[p] = q;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}